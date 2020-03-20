#pragma once

#define _GNU_SOURCE 1
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <sched.h>
#include <stdlib.h>

int64_t *sumEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer);
int64_t *sumNotEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer);
void *sumPart(void *args);
