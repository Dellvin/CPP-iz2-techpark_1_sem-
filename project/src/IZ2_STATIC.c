#include "IZ2_STATIC.h"

int64_t *sumEven(const int64_t *arr, size_t size, int64_t *answer) {
    if (arr == NULL)
        return NULL;
    for (size_t i = 0; i < size; ++i) {
        if ((arr[i] % 2) == 0)
            *(answer) += arr[i];
    }
    return answer;
}

int64_t *sumNotEven(const int64_t *arr, size_t size, int64_t *answer) {
    if (arr == NULL)
        return NULL;
    for (size_t i = 1; i < size; ++i) {
        if ((arr[i] % 2) != 0)
            *(answer) += arr[i];
    }
    return answer;
}
