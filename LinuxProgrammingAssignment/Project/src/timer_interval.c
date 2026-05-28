#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

/* CONFIGURATION */
#define INPUT_POLL_NS 100000000LL // 100 ms
#define DEFAULT_PERIOD_NS 1000000LL // 1 ms
#define FREQ_FILE "freq.txt"
#define LOG_FILE "log.txt"

/* GLOBAL VARIABLES */
static volatile long long g_T = 0;
static volatile long long g_period_ns = DEFAULT_PERIOD_NS; // Default period of 1 ms
static volatile int g_new_sample = 0;
// Mutex for protecting access to g_T and new sample flag
static pthread_mutex_t T_sample_mutex = PTHREAD_MUTEX_INITIALIZER;
// Condition variable to signal LOGGING thread when a new sample is available
static pthread_cond_t T_cond = PTHREAD_COND_INITIALIZER;
// Mutex for protecting access to period updates from INPUT thread
static pthread_mutex_t period_mutex = PTHREAD_MUTEX_INITIALIZER;
/*Flag to start/stop the program*/
static volatile int g_running = 1;

/*FUNCTION DEFINITIONS */
// Sleep until the next period
static void sleep_until(struct timespec *next, long long period){
    next->tv_nsec += (long)(period % 1000000000LL);
    next->tv_sec += (long)(period / 1000000000LL);
    // Handle overflow of nanoseconds
    if (next->tv_nsec >= 1000000000LL) {
        next->tv_nsec -= 1000000000LL;
        next->tv_sec += 1;
    }
    while (clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, next, NULL) == -1)
        ; // Re/*try if interrupted by signal
}

// Get current time in nanoseconds
static inline long long now_ns(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

/* THREAD FUNCTIONS */
/*
Thread INPUT
Description: 
    1.Thread gets input from the user and updates the global variable g_input. 
    2.It also signals the SAMPLE thread that a new input is available.
*/
static void *thread_input(void *arg)
{
    (void)arg;

    // Save the previous content to detect changes
    char prev_content[64] = "";
    // Sleep time specification for polling - 100 ms
    struct timespec sleep_ts = {
        .tv_sec = 0,
        .tv_nsec = INPUT_POLL_NS};

    while (g_running)
    {
        // Sleep for a short period to avoid busy waiting
        nanosleep(&sleep_ts, NULL);

        FILE *fp = fopen(FREQ_FILE, "r");
        // If the file doesn't exist, skip this iteration
        if (!fp)
            continue;

        char buf[64] = "";
        // Read the content of the file
        if (!fgets(buf, sizeof(buf), fp))
        {
            fclose(fp);
            continue;
        }
        fclose(fp);

        // Remove trailing newline and whitespace characters
        size_t len = strlen(buf);
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r' ||
                           buf[len - 1] == ' '))
            buf[--len] = '\0';

        // If the content hasn't changed, skip this iteration
        if (strcmp(buf, prev_content) == 0)
            continue;

        // Convert the value to a long long integer
        char *endptr = NULL;
        long long new_period = strtoll(buf, &endptr, 10);
        if (endptr == buf || new_period <= 0)
        {
            fprintf(stderr, "INPUT: giá trị không hợp lệ: \"%s\"\n", buf);
            continue;
        }

        // Update the global variable g_period_ns with the new value
        pthread_mutex_lock(&period_mutex);
        g_period_ns = new_period;
        pthread_mutex_unlock(&period_mutex);

        // Save the new content to detect future changes
        strncpy(prev_content, buf, sizeof(prev_content) - 1);
        // Print the updated period to the console
        printf("INPUT: cập nhật chu kỳ X = %lld ns\n", new_period);
        fflush(stdout);
    }
    return NULL;
}

/*
Thread LOGGING
Description:
    1.Thread waits for a signal from the SAMPLE thread that a new sample is available.
    2.When it receives the signal, it logs the current time and the interval since the last sample to a file.
*/
static void *thread_logging(void *arg)
{   
    (void)arg;
    long long prev_T = 0;
    // Flag to indicate if it's the first interval calculation
    int first_interval_flag = 1;

    // Open the log file for writing
    FILE *log_fp = fopen(LOG_FILE, "w");
    if (!log_fp) {
        perror("Failed to open log file");
        return NULL;
    }
    // Create the log file header
    fprintf(log_fp, "Current Time (ns), Interval (ns)\n");
    fflush(log_fp);

    while (g_running) {
        //Wait for a new sample signal from the SAMPLE thread 
        pthread_mutex_lock(&T_sample_mutex);
        // Optimize the waiting time by using a flag to indicate when a new sample is available
        while (!g_new_sample && g_running) {
            pthread_cond_wait(&T_cond, &T_sample_mutex);
        }
        // If the program is no longer running, exit the loop
        if (!g_running) {
            pthread_mutex_unlock(&T_sample_mutex);
            break;
        }
        //Update the current time and reset the new sample flag
        long long current_T = g_T;
        // Reset the flag for the next sample
        g_new_sample = 0;
        pthread_mutex_unlock(&T_sample_mutex);

        // Calculate the interval
        long long interval = first_interval_flag ? 0 : current_T - prev_T;
        first_interval_flag = 0;
        
        // Log the current time and interval to the file
        // printf("Current time: %lld ns, Interval: %lld ns\n", current_T, interval);
        fprintf(log_fp, "%lld, %lld\n", current_T, interval);
        fflush(log_fp);

        // Update prev_T for the next interval calculation
        prev_T = current_T;
    }
    // Close the log file before exiting
    fclose(log_fp);
    return NULL;
}

/*
Thread SAMPLE
Description:
    1.Thread gets the current time in nanoseconds and updates the global variable g_T.
    2.It also signals the LOGGING thread that a new sample is available.
*/
static void *thread_sample(void *arg)
{   
    struct timespec next;
    // Get the current time as the baseline for sleeping
    clock_gettime(CLOCK_REALTIME, &next);

    while (g_running) { 
        // Sleep until the next period
        pthread_mutex_lock(&period_mutex);
        long long period = g_period_ns;
        pthread_mutex_unlock(&period_mutex);

        // Sleep until the next period 
        sleep_until(&next, period);

        // Get current time in nanoseconds and update global variable g_T
        pthread_mutex_lock(&T_sample_mutex);
        long long current_time_ns = now_ns();
        // Update global variable g_T
        g_T = current_time_ns;
        // Set the flag to indicate a new sample is available
        g_new_sample = 1;
        // Signal the LOGGING thread that a new sample is available
        pthread_cond_signal(&T_cond);
        pthread_mutex_unlock(&T_sample_mutex);
    }
    return NULL;
}


int main()
{   
    // Check if the frequency file exists, if not create it with the default period
    FILE *freq_fp = fopen(FREQ_FILE, "r");
    if (!freq_fp) {
        freq_fp = fopen(FREQ_FILE, "w");
        if (freq_fp) {
            // Write the default period to the file
            fprintf(freq_fp, "%lld\n", DEFAULT_PERIOD_NS);
            fclose(freq_fp);
        } else {
            perror("Failed to create frequency file");
            return 1;
        }
    } else {
        fclose(freq_fp);
    }

    // Initialize threads for SAMPLE, LOGGING, and INPUT
    pthread_t t_logging, t_sample, t_input;

    // Create the LOGGING thread
    if (pthread_create(&t_logging, NULL, thread_logging, NULL) != 0) {
        perror("Failed to create LOGGING thread");
        return 1;
    }
    // Create the SAMPLE thread
    if (pthread_create(&t_sample, NULL, thread_sample, NULL) != 0) {
        perror("Failed to create SAMPLE thread");
        return 1;
    }
    // Create the INPUT thread
    if (pthread_create(&t_input, NULL, thread_input, NULL) != 0) {
        perror("Failed to create INPUT thread");
        return 1;
    }
    
    // Wait for threads to finish
    pthread_join(t_logging, NULL);
    pthread_join(t_sample, NULL);
    pthread_join(t_input, NULL);

    return 0;
}