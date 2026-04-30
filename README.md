# C_Knowledge
C Programming language

## Exercises from "The C Programming Language" 2nd Edition by Brian W. Kernighan and Dennis M. Ritchie

### Chapter 1: A Tutorial Introduction
1-1. Run the "hello, world" program on your system. Experiment with leaving out parts of the program, to see what error messages you get.  
1-2. Experiment to find out what happens when printf's argument string contains \c, where c is some character not listed above.  
1-3. Modify the temperature conversion program to print a heading above the table.  
1-4. Write a program to print the corresponding Celsius to Fahrenheit table.  
1-5. Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.  
1-6. Verify that the expression getchar() != EOF is 0 or 1.  
1-7. Write a program to print the value of EOF.  
1-8. Write a program to count blanks, tabs, and newlines.  
1-9. Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.  
1-10. Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.  
1-11. How would you test the word count program? What kinds of input are most likely to uncover bugs if there are any?  
1-12. Write a program that prints its input one word per line.  
1-13. Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.  
1-14. Write a program to print a histogram of the frequencies of different characters in its input.  
1-15. Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.  
1-16. Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lines, and as much as possible of the text.  
1-17. Write a program to print all input lines that are longer than 80 characters.

### Chapter 2: Types, Operators, and Expressions
2-1. Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point types.  
2-2. Write a loop equivalent to the for loop above without using && or ||.  
2-3. Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.  
2-4. Write an alternate version of squeeze(s1,s2) that deletes each character in s1 that matches any character in the string s2.  
2-5. Write the function any(s1,s2), which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.)  
2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits of x unchanged.  
2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.

### Chapter 3: Control Flow
3-1. Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside). Write a version with only one test inside the loop and measure the difference in run-time.  
3-2. Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters.  
3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.  
3-4. In a two's complement number system, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2^{wordsize-1}). Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.

### Chapter 4: Functions and Program Structure
4-1. Write the function strrindex(s,t) which returns the position of the rightmost occurrence of t in s, or -1 if there is none.  
4-2. Extend atof to handle scientific notation of the form 123.45e-6 where a floating-point number may be followed by e or E and an optionally signed exponent.  
4-3. Given the basic framework, it's straightforward to extend the calculator. Add the modulus (%) operator and provisions for negative numbers.  
4-4. Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack.  
4-5. Add access to library functions like sin, exp, and pow. See <math.h> in Appendix B, Section 4.  
4-6. Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.) Add a variable for the most recently printed value.  
4-7. Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know about buf and bufp, or should it just use ungetch?  
4-8. Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.  
4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to be if an EOF is pushed back, then implement your design.  
4-10. An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise the calculator to use this approach.

### Chapter 5: Pointers and Arrays
5-1. As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input.  
5-2. Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?  
5-3. Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s.  
5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise.  
5-5. Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.  
5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).  
5-7. Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program?  
5-8. There is no error checking in day_of_year or month_day. Remedy this defect.  
5-9. Rewrite the routines day_of_year and month_day with pointers instead of indexing.  
5-10. Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. For example, expr 2 3 4 + * evaluates 2 * (3+4).  
5-11. Modify the program entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.  
5-12. Extend entab and detab to accept the shorthand entab -m +n to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior.  
5-13. Write the program tail, which prints the last n lines of its input. By default, n is 10, say, but it can be changed by an optional argument. The program should behave rationally no matter how unreasonable the input or the value of n.  
5-14. Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n.

### Chapter 6: Structures
6-1. Our version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines. Write a better version.  
6-2. Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters, but different somewhere thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set from the command line.  
6-3. Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. Remove noise words like "the," "and," etc.  
6-4. Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. Precede each word by its count.  
6-5. Write a function undef that will remove a name and definition from the table maintained by lookup and install.  
6-6. Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs, based on the routines of this section. You may also find getch and ungetch helpful.

### Chapter 7: Input and Output
7-1. Write a program that converts upper case to lower or lower case to upper, depending on the name it is invoked with, as found in argv[0].  
7-2. Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.  
7-3. Revise minprintf to handle more of the other facilities of printf.  
7-4. Write a private version of scanf analogous to minprintf from the previous section.  
7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion.  
7-6. Write a program to compare two files, printing the first line where they differ.

### Chapter 8: The UNIX System Interface
8-1. Rewrite the program cat from Chapter 7 using read, write, open, and close instead of their standard library equivalents. Perform experiments to determine the relative speeds of the two versions.  
8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code size and execution speed.  
8-3. Design and write _flushbuf, fflush, and fclose.  
8-4. The standard library function int fseek(FILE *fp, long offset, int origin) is identical to lseek except that fp may be a file stream instead of a file descriptor and the return value is an int status, not a position. Write fseek. Make sure that your fseek coordinates properly with the buffering done for the other functions of the library.  
8-5. Modify the fsize program to print the other information contained in the inode entry.  
8-6. The standard library function calloc(n, sizeof(object)) could be implemented as a single call to malloc or by a call to malloc followed by memset to initialize to zero. Profile the two approaches to see which is better.