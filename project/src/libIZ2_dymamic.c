#include "libIZ2_dymamic.h"
#include <errno.h>

#define handle_error_en(en, msg) \
               do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

enum typeSum {
    EVEN,
    NOT_EVEN
};

typedef struct threadParams {
    int64_t *arr;
    enum typeSum type;
    size_t begin;
    size_t end;
    int64_t sum;
} threadParams;


static void *sumPart(void *args);

static void setSruct(threadParams *obj, int64_t *arr, enum typeSum type, size_t begin, size_t end, int64_t sum);

static void getAnswer(int64_t *answer, threadParams *arr, uint16_t threadCount);

static void deleter(threadParams **arr, int64_t **answer, pthread_t **threads);

int64_t *sumEvenThread(int64_t *arr, size_t size) {
    int64_t *answer = (int64_t*)malloc(sizeof(int64_t));
    uint16_t threadCount=8;
    if(!answer){
        return NULL;
    }
    if (arr == NULL){
        deleter(NULL, &answer, NULL);
        return NULL;
    }

    threadParams *data = (threadParams *) malloc(threadCount * sizeof(threadParams));
    if (!data){
        deleter(NULL, &answer, NULL);
        return NULL;
    }
    pthread_t *threads = (pthread_t *) malloc(threadCount * sizeof(pthread_t));
    for (uint16_t i = 0; i < threadCount; i++) {
        setSruct(&data[i], arr, EVEN, (size_t) ((size / threadCount) * i),
                 (size_t) (((size / threadCount) * (i + 1)) - 1), 0);
        int status=pthread_create(&(threads[i]), NULL, sumPart, &data[i]);
        if(status){
            handle_error_en(status, "pthread_create");
            deleter(&data, &answer, &threads);
            return NULL;
        }
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);
        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpuset);
    }



    for (uint16_t i = 0; i < threadCount; i++){
        int stat = pthread_join(threads[i], NULL);
        if(stat){
            handle_error_en(stat, "pthread_join");
            deleter(&data, &answer, &threads);
//            free(answer);
//            free(data);
//            free(threads);
            return NULL;
        }
    }
    getAnswer(answer, &data[0], threadCount);
    deleter(&data, NULL, &threads);
//    free(data);
//    free(threads);
    return answer;
}


int64_t *sumNotEvenThread(int64_t *arr, size_t size) {
    int64_t *answer=(int64_t*)malloc(sizeof(int64_t));
    if(!answer)
        return NULL;
    uint16_t threadCount=8;
    if (arr == NULL){
        deleter(NULL, &answer, NULL);
        return NULL;
    }
    threadParams *data = (threadParams*) malloc(threadCount * sizeof(threadParams));
    if (!data){
        deleter(NULL, &answer, NULL);
        return NULL;
    }
    pthread_t *threads = (pthread_t *) malloc(threadCount * sizeof(pthread_t));
    if (!threads) {
        deleter(&data, &answer, NULL);
        return NULL;
    }
    for (uint16_t i = 0; i < threadCount; i++) {
        size_t end=(size_t) ((size / threadCount) * (i + 1));
        if ((i + 1) == threadCount) end += 1;
        setSruct(&data[i], arr, NOT_EVEN, (size_t) ((size / threadCount) * i),
                end, 0);
        int status=pthread_create(&(threads[i]), NULL, sumPart, &data[i]);
        if (status){
            handle_error_en(status, "pthread_create");
            deleter(&data, &answer, &threads);
            return NULL;
        }
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);
        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpuset);
    }
    for (uint16_t i = 0; i < threadCount; i++){
        int stat=pthread_join(threads[i], NULL);
        if(stat){
            handle_error_en(stat, "pthread_join");
            deleter(&data, &answer, &threads);
            return NULL;
        }
    }
    getAnswer(answer, &data[0], threadCount);
    deleter(&data, NULL, &threads);
    return answer;
}


static void *sumPart(void *args) {
    threadParams *data = (threadParams *) args;
    if (data->type == EVEN) {
        for (uint64_t i = data->begin; i < data->end; ++i) {
            if ((data->arr[i] % 2) == 0) {
                data->sum += data->arr[i];
            }
        }
    }
    if (data->type == NOT_EVEN) {
        for (uint64_t i = data->begin; i < data->end; ++i) {
            if ((data->arr[i] % 2) != 0) {
                data->sum += data->arr[i];
            }
        }
    }
    return NULL;
}


static void setSruct(threadParams *obj, int64_t *arr, enum typeSum type, size_t begin, size_t end, int64_t sum){
    obj->arr=arr;
    obj->type=type;
    obj->begin=begin;
    obj->end=end;
    obj->sum=sum;
}

static void getAnswer(int64_t *answer, threadParams *arr, uint16_t threadCount){
    *(answer) = 0;
    for (uint16_t i = 0; i < threadCount; i++) {
        *(answer) += (arr+i)->sum;
    }
}

static void deleter(threadParams **arr, int64_t **answer, pthread_t **threads){
    if(arr) free(*arr);
    if(answer) free(*answer);
    if(threads) free(*threads);
}
