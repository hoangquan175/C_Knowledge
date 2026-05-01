/*
Exercises:
3-1. Our binary search makes two tests inside the loop, when one would suffice 
(at the price of more tests outside). 
Write a version with only one test inside the loop and measure the difference in run-time.  
*/
#include <stdio.h>
#include "header.h"

// Binary search function with one test inside the loop
int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    // After the loop, low == high. Check if the element at this position matches x.
    if (low < n && v[low] == x) {
        return low; // Element found at index low
    } else {
        return -1; // Element not found
    }
}


int main() {
    int v[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19}; // Example sorted array
    int n = sizeof(v) / sizeof(v[0]);
    int x = 19; // Element to search for 
    int result = binsearch(x, v, n);
    if (result != -1) {
        printf("Element %d found at index: %d\n", x, result);
    } else {
        printf("Element %d not found in the array.\n", x);
    }
    return 0;
}