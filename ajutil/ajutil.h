#ifndef JUTIL_H
#define JUTIL_H
#include <sys/time.h>
#include "bTree.h"
#include "list.h"

#ifndef SWAP
#define SWAP(a,b) a=a^b;b=b^a;a=a^b;
#endif

typedef struct Timer {
    struct timeval st, fn;
} timer;

// arr is the array
// st is the first address that can be accessed
// fn is the last address that can be accessed, not the array size
void quicksort(int arr[], unsigned int st, unsigned int fn);

// unsigned quicksort
void quicksortu(unsigned int arr[], unsigned int st, unsigned int fn);

// counting sort
// k is the range [off, off+k];
int* countingsort(int arr[], unsigned int len, unsigned int k, unsigned int off);

// generic time functions
void time_start(timer*);// saves to start
void time_stop(timer*);// saves to finish
void time_lap(timer*);// pushes finish to start and then saves, must call after stop
double time_delta(timer*);//

// assumes base 10
int iatoi(int*, unsigned int);// converts an integer array to an integer, array and array size

// converts an integer to a character array with a given base
// returns an array made with dynamic memory NOTE: REMEMBER TO DEALLOCATE
char* itoa(int num, unsigned int base);

// same as above but for unsigned integers
char* uintoa(unsigned int num, unsigned int base);

// euclidean greatest common divisor algorithim
unsigned int euclideanAlgorithm(unsigned int, unsigned int);

// euclidean linear combination
// int linearCombination(int, int, int*, int*);

#endif // JUTIL_H
