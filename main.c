/*Условие ИЗ№1:
Создать структуру для хранения информации об HTML-теге: его имени, признаке «открывающий/закрывающий» и атрибутах тега.
 Составить с ее использованием программу, включающую в себя функцию, принимающую на вход текстовую строку с одним тегом.
 На выход функция должна возвращать указатель на инициализированную структуру.
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdint.h>
#include <sched.h>
#include "./libraries/dynamic/libIZ2_dymamic.h"
#include "./libraries/static/IZ2_STATIC.h"
#include <pthread.h>


//enum typeSum{
//    EVEN,
//    NOT_EVEN
//};
//home/dellvin/CLionProjects/iz2/main.c
//typedef struct threadParams{
//    int64_t *arr;
//    enum typeSum type;
//    size_t begin;
//    size_t end;
//    int64_t sum;
//}threadParams;
//
//int64_t sumEven(const int64_t *arr, size_t size);
//
//int64_t sumNotEven(const int64_t *arr, size_t size);
//
//void *sumPart(void *args);
//
//int64_t *sumEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer);
//
//int64_t *sumNotEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer);
//


int main() {
    int64_t *arr;
    size_t size=100000000;
    arr=(int64_t*)malloc(size*sizeof(int64_t));
    if(!arr) return 0;
    for(int i=0;i<size;++i){
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
//
//int64_t sumEven(const int64_t *arr, size_t size){
//    int64_t sum=0;
//    for(size_t i=0;i<size; ++i){
//        if((arr[i]%2)==0)
//            sum+=arr[i];
//    }
//    return sum;
//}
//
//int64_t sumNotEven(const int64_t *arr, size_t size){
//    int64_t sum=0;
//    for(size_t i=1;i<size; ++i){
//        if((arr[i]%2)!=0)
//            sum+=arr[i];
//    }
//    return sum;
//}
//
//
//int64_t *sumEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer){
//    threadParams **data=(threadParams **)malloc(threadCount*sizeof(threadParams*));
//    if(!data)
//        return NULL;
//    pthread_t *threads=(pthread_t *)malloc(threadCount*sizeof(pthread_t));
//    if(!threads){
//        free(data);
//        return NULL;
//    }
//    for(uint16_t i=0;i<threadCount;i++){
//        data[i]=(threadParams *)malloc(sizeof(threadParams));
//        if(!data[i]){
//            free(threads);
//            for(uint16_t j=0;j<i;j++) free(data[j]);
//            free(data);
//            return NULL;
//        }
//        data[i]->arr=arr;
//        data[i]->sum=0;
//        data[i]->type=EVEN;
//        data[i]->begin=(size_t)((size/threadCount)*i);
//        data[i]->end=(size_t)(((size/threadCount)*(i+1))-1);
//
//
//        pthread_create(&(threads[i]), NULL, sumPart, data[i]);
//        cpu_set_t cpuset;
//        CPU_ZERO(&cpuset);
//        CPU_SET(i, &cpuset);
//        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpuset);
//    }
//
//
//    for(uint16_t i = 0; i < threadCount; i++)
//        pthread_join(threads[i], NULL);
//
//    *(answer)=0;
//    for (uint16_t i=0; i<threadCount; i++) {
//        *(answer)+=data[i]->sum;
//    }
//
//
//    for (uint16_t i=0; i<threadCount; i++) {
//        free(data[i]);
//    }
//    free(data);
//    free(threads);
//    return answer;
//}
//
//
//int64_t *sumNotEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer){
//
//    threadParams **data=(threadParams **)malloc(threadCount*sizeof(threadParams*));
//    if(!data)
//        return NULL;
//    pthread_t *threads=(pthread_t *)malloc(threadCount*sizeof(pthread_t));
//    if(!threads){
//        free(data);
//        return NULL;
//    }
//    for(uint16_t i=0;i<threadCount;i++){
//        data[i]=(threadParams *)malloc(sizeof(threadParams));
//        if(!data[i]){
//            free(threads);
//            for(uint16_t j=0;j<i;j++) free(data[j]);
//            free(data);
//            return NULL;
//        }
//        data[i]->arr=arr;
//        data[i]->sum=0;
//        data[i]->type=NOT_EVEN;
//        data[i]->begin=(size_t)((size/threadCount)*i);
//        data[i]->end=(size_t)((size/threadCount)*(i+1));
//        if((i+1)==threadCount) data[i]->end+=1;
//        pthread_create(&(threads[i]), NULL, sumPart, data[i]);
//        cpu_set_t cpuset;
//        CPU_ZERO(&cpuset);
//        CPU_SET(i, &cpuset);
//        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpuset);
//    }
//
//
//    for(uint16_t i = 0; i < threadCount; i++)
//        pthread_join(threads[i], NULL);
//
//    *(answer)=0;
//    for (uint16_t i=0; i<threadCount; i++) {
//        *(answer)+=data[i]->sum;
//    }
//
//    for (uint16_t i=0; i<threadCount; i++) {
//        free(data[i]);
//    }
//    free(data);
//    free(threads);
//    return answer;
//}
//
//
//void *sumPart(void *args){
//    threadParams *data=(threadParams*)args;
//    if(data->type==EVEN){
//        for(int64_t i= data->begin;i<data->end;++i){
//            if((data->arr[i]%2)==0){
//                data->sum+=data->arr[i];
//            }
//        }
//    }
//    if(data->type==NOT_EVEN){
//        for(int64_t i= data->begin;i<data->end;++i){
//            if((data->arr[i]%2)!=0){
//                data->sum+=data->arr[i];
//            }
//        }
//    }
//    return NULL;
//}
