#include <stdint.h>
#include <stdlib.h>

double *mem_arrayAlloc(int size, double setValue);

void memclear(void *ptr, int8_t value, size_t size);

void mem_memcpy(void *dest, void *orig, size_t size);
