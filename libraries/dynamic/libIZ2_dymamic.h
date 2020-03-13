int64_t *sumEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer);

int64_t *sumNotEvenThread(int64_t *arr, size_t size, uint16_t threadCount, int64_t *answer);

void *sumPart(void *args);
