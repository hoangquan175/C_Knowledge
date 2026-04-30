# C Coding Convention for Exercises

## 1. File Structure

- inc/*.h       → Header files (declarations)
- src/*.c          → Implementation files


## 2. Naming Conventions
- **Functions**: `snake_case` → `calculate_sum()`, `print_menu()`
- **Variables**: `snake_case` → `user_input`, `total_count`
- **Constants**: `UPPER_SNAKE_CASE` → `MAX_SIZE`, `PI_VALUE`

## 3. Indentation & Spacing
- One blank line between functions
- Space around operators: `a + b`, not `a+b`

## 4. Comments

// Single line comment for brief explanation

/* Multi-line comment
   for longer explanations
   or copyright notices */


## 5. Function Structure
// Function comment explaining purpose
int calculate_sum(int a, int b) {
    int result = a + b;
    return result;
}


## 6. Header Guard (in .h files)

#ifndef HEADER_H
#define HEADER_H

// Declarations here

#endif


## 7. Main Function
#include <stdio.h>

int main() {
    // Your code here
    return 0;
}

