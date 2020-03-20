//#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdint.h>
#include <sched.h>
#include "libIZ2_dymamic.h"
#include "IZ2_STATIC.h"
#include <pthread.h>


int main() {
    int64_t *arr;
    size_t size=100000000;
    arr=(int64_t*)malloc(size*sizeof(int64_t));
    if(!arr) return 0;
    for(size_t i=0;i<size;++i){
        arr[i]=i;
    }

    int64_t answer;
    clock_t start;
    start = clock();
    if(!sumNotEvenThread(arr, size, 8, &answer)){
        free(arr);
        return 0;
    }
    printf("Answer with thread NOT even: %ld\n", answer);
    if(!sumEvenThread(arr, size, 8, &answer)) {
        free(arr);
        return 0;
    }
    printf("Answer with thread even: %ld\n", answer);
    clock_t finish = clock();
    clock_t total=finish-start;
    printf("Total thread time: %lu\n", total);

    start = clock();
    printf("Answer without thread even: %ld\nAnswer not even: %ld\n", sumEven(arr, size), sumNotEven(arr, size));
    finish = clock();
    total=finish-start;
    printf("Total non thread time: %lu\n", total);

    free(arr);
    return 0;
}
