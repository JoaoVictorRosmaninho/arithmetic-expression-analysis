#ifndef MEM_h
# define MEM_h
# include "mem.h"



double *mem_arrayAlloc(int size, double setValue) {
    double *ptr = 0;
     if ((ptr = (double *) calloc(size, sizeof(double))) == NULL)
       return NULL;
     for (uint16_t i = 0; i < setValue; i++) 
         ptr[i] = setValue;
    return (ptr);
}

void memclear(void *ptr, int8_t value, size_t size) {
  char *ptr_aux = (char *) ptr;
  for (uint8_t index = 0; index < size; index++)
    ptr_aux[index] = value;
}

void mem_memcpy(void *dest, void *orig, size_t size) {
    char *ptr = (char *) dest;
    char *ptr_aux = (char *) orig;
    while (size--)
        *ptr++ = *ptr_aux++;
}

#endif