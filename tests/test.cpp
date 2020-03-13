//
// Created by sergiy on 06.03.2020.
//
#include "gtest/gtest.h"
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdint.h>
#include <sched.h>
#include "../libraries/dynamic/libIZ2_dymamic.h"
#include "../libraries/static/IZ2_STATIC.h"

TEST(test, Test2) {
ASSERT_EQ(true, true);

    int64_t *arr;
    size_t size=100000000;
    arr=(int64_t*)malloc(size*sizeof(int64_t));
    if(!arr) return;
    for(int i=0;i<size;++i){
        arr[i]=i;
    }

    int64_t answer1;
    int64_t answer2;
    int64_t answer3;
    int64_t answer4;
    clock_t start;
    start = clock();
    if(!sumNotEvenThread(arr, size, 8, &answer1)){
        free(arr);
        return;
    }
    EXPECT_EQ(answer1, 2500000000000000);
    printf("Answer with thread NOT even: %ld\n", answer1);
    if(!sumEvenThread(arr, size, 8, &answer2)) {
        free(arr);
        return;
    }
    EXPECT_EQ(answer2, 2499999950000000);
    printf("Answer with thread even: %ld\n", answer2);
    clock_t finish = clock();
    clock_t total=finish-start;
    printf("Total thread time: %lu\n", total);

    start = clock();
    answer3=sumEven(arr, size);
    answer4=sumNotEven(arr, size);

    printf("Answer without thread even: %ld\nAnswer not even: %ld\n", answer3, answer4);
    finish = clock();
    total=finish-start;
    printf("Total non thread time: %lu\n", total);

    EXPECT_EQ(answer1, answer4);
    EXPECT_EQ(answer2,answer3);
    free(arr);
}
