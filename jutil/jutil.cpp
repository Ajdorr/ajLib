#include <sys/time.h>
#include <stdlib.h>
#include "jutil.h"

void quicksort(int arr[], unsigned int st, unsigned int fn) {
    unsigned int l, r, piv;

    if ( (int)(fn - st) < 1) {
        return;
    }
    else if ((fn - st) == 1) {
        if (arr[st] > arr[fn]) {
            SWAP(arr[st],arr[fn]);
        }
        return;
    }

    piv = st;
    l = st + 1;
    r = fn;

    while ((l != r) && (l < r)) {
        if ( (arr[l] > arr[piv]) && (arr[r] < arr[piv]) ) {
            SWAP(arr[l], arr[r]);
            l++;
            r--;
        }
        else {
            if (arr[l] <= arr[piv])
                l++;
            if (arr[r] >= arr[piv])
                r--;
        }
    }
    if (l > r) {
        l--; // make them equal
    }
    if (arr[l] < arr[piv]) {
        SWAP(arr[l], arr[piv]);
        l--;
        r = (r >= fn) ? fn : r+1;
    }
    else if (--l != piv) {
        SWAP(arr[l], arr[piv]);
        l--;
    }
    // pivot was smallest element

    quicksort(arr, st, l);
    quicksort(arr, r, fn);
}

int* countingsort(int arr[], unsigned int len, unsigned int k, unsigned int off){
    unsigned int i;
    int count[k], *ret, t;

    ret = new int[len];

    for (i = 0; i < k; i++)
        count[i]=0;

    for (i = 0; i < len; i++){
        t = arr[i] - off;
        count[t]++;
    }

    for (i = 0; i < k-1; i++)
        count[i+1] += count[i];

    for (i = len-1; i < len; i--){
        ret[count[arr[i]-off]-1] = arr[i];
        count[arr[i]-off]--;
    }

    return ret;
}

void time_start(timer *t) {
    gettimeofday(&(t->st), NULL);
}

void time_stop(timer *t) {
    gettimeofday(&(t->fn), NULL);
}

void time_lap(timer *t) {
    gettimeofday(&(t->fn), NULL);
}

double time_delta(timer *t) {
    return ((double)(t->fn.tv_sec - t->st.tv_sec) + (double)(t->fn.tv_usec - t->st.tv_usec)/1000000);
}

int iatoi(int *a, unsigned int sz) {
    int ret = 0;
    unsigned int i;

    for (i=0; i < sz; i++)
        ret = 10*ret + a[i];

    return ret;
}



