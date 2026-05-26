#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


/* Global variables */
static volatile long long g_T = 0;
static volatile int g_period_ns = 1000000; // Default period of 1 ms
static pthread_mutex_t T_period_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t T_cond = PTHREAD_COND_INITIALIZER;

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
        ; // Retry if interrupted by signal
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
    long long prev_T = 0;
    while (1) {
        /* Wait for a new sample signal from the SAMPLE thread */
        pthread_mutex_lock(&T_period_mutex);
        pthread_cond_wait(&T_cond, &T_period_mutex);
        long long current_T = g_T;
        long long interval = current_T - prev_T;
        pthread_mutex_unlock(&T_period_mutex);
        printf("Current time: %lld ns, Interval: %lld ns\n", current_T, interval);
        prev_T = current_T;
    }
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
    while (1) { 
        // Sleep until the next period
        pthread_mutex_lock(&T_period_mutex);
        long long period = g_period_ns;
        pthread_mutex_unlock(&T_period_mutex);
        // Sleep until the next period 
        sleep_until(&next, period);
        /*1. Get current time in nanoseconds and update global variable g_T */
        pthread_mutex_lock(&T_period_mutex);
        long long current_time_ns = now_ns();
        // Update global variable g_T (not shown here, as it's not defined in this snippet)
        g_T = current_time_ns;
        // Signal the LOGGING thread that a new sample is available
        pthread_cond_signal(&T_cond);
        pthread_mutex_unlock(&T_period_mutex);
    }
    return NULL;
}


int main()
{
    pthread_t t_logging, t_sample, t_input;

    if (pthread_create(&t_logging, NULL, thread_logging, NULL) != 0) {
        perror("Failed to create LOGGING thread");
        return 1;
    }
    if (pthread_create(&t_sample, NULL, thread_sample, NULL) != 0) {
        perror("Failed to create SAMPLE thread");
        return 1;
    }
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