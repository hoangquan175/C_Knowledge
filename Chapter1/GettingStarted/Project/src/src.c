// Exercises:
// 1-1. Run the "hello, world" program on your system. 
// Experiment with leaving out parts of the program, to see 
// what error messages you get.  
// 1-2. Experiment to find out what happens when printf's argument 
// string contains \c, where c is some character not listed above.
#include <stdio.h>

int main() {
    // 1-1. Run the "hello, world" program on your system. 
    // Experiment with leaving out parts of the program, to see 
    // what error messages you get.
    printf("Hello, World!\n");

    // 1-2. Experiment to find out what happens when printf's argument 
    // string contains \c, where c is some character not listed above.
    printf("This is a test of escape sequences: \n\t\\ \" \' \a \b \f \r \v\n");
    return 0;
}