#include "libIZ2_dymamic.h"


enum typeSum{
    EVEN,
    NOT_EVEN
};

typedef struct threadParams{
    int64_t *arr;
    enum typeSum type;
    size_t begin;
    size_t end;
    int64_t sum;
}threadParams;

int64_t *sumEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer){
    threadParams **data=(threadParams **)malloc(threadCount*sizeof(threadParams*));
    if(!data)
        return NULL;
    pthread_t *threads=(pthread_t *)malloc(threadCount*sizeof(pthread_t));
    if(!threads){
        free(data);
        return NULL;
    }
    for(uint16_t i=0;i<threadCount;i++){
        data[i]=(threadParams *)malloc(sizeof(threadParams));
        if(!data[i]){
            free(threads);
            for(uint16_t j=0;j<i;j++) free(data[j]);
            free(data);
            return NULL;
        }
        data[i]->arr=arr;
        data[i]->sum=0;
        data[i]->type=EVEN;
        data[i]->begin=(size_t)((size/threadCount)*i);
        data[i]->end=(size_t)(((size/threadCount)*(i+1))-1);


        pthread_create(&(threads[i]), NULL, sumPart, data[i]);
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);
        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpuset);
    }


    for(uint16_t i = 0; i < threadCount; i++)
        pthread_join(threads[i], NULL);

    *(answer)=0;
    for (uint16_t i=0; i<threadCount; i++) {
        *(answer)+=data[i]->sum;
    }


    for (uint16_t i=0; i<threadCount; i++) {
        free(data[i]);
    }
    free(data);
    free(threads);
    return answer;
}


int64_t *sumNotEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer){

    threadParams **data=(threadParams **)malloc(threadCount*sizeof(threadParams*));
    if(!data)
        return NULL;
    pthread_t *threads=(pthread_t *)malloc(threadCount*sizeof(pthread_t));
    if(!threads){
        free(data);
        return NULL;
    }
    for(uint16_t i=0;i<threadCount;i++){
        data[i]=(threadParams *)malloc(sizeof(threadParams));
        if(!data[i]){
            free(threads);
            for(uint16_t j=0;j<i;j++) free(data[j]);
            free(data);
            return NULL;
        }
        data[i]->arr=arr;
        data[i]->sum=0;
        data[i]->type=NOT_EVEN;
        data[i]->begin=(size_t)((size/threadCount)*i);
        data[i]->end=(size_t)((size/threadCount)*(i+1));
        if((i+1)==threadCount) data[i]->end+=1;
        pthread_create(&(threads[i]), NULL, sumPart, data[i]);
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);
        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpuset);
    }


    for(uint16_t i = 0; i < threadCount; i++)
        pthread_join(threads[i], NULL);

    *(answer)=0;
    for (uint16_t i=0; i<threadCount; i++) {
        *(answer)+=data[i]->sum;
    }

    for (uint16_t i=0; i<threadCount; i++) {
        free(data[i]);
    }
    free(data);
    free(threads);
    return answer;
}


void *sumPart(void *args){
    threadParams *data=(threadParams*)args;
    if(data->type==EVEN){
        for(uint64_t i= data->begin;i<data->end;++i){
            if((data->arr[i]%2)==0){
                data->sum+=data->arr[i];
            }
        }
    }
    if(data->type==NOT_EVEN){
        for(uint64_t i= data->begin;i<data->end;++i){
            if((data->arr[i]%2)!=0){
                data->sum+=data->arr[i];
            }
        }
    }
    return NULL;
}
