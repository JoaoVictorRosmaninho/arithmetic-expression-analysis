#include <stdint.h>
#include <stdlib.h>

/* temporario */
#define str_isNumber(ch) ((ch) >= '0' && (ch) <= '9')

#define str_isDelimiter(ch) ((ch) >= '\t' &&  (ch) <= '\r') || ((ch) == ' ')

#ifndef BIARRAY 
# define BIARRAY
    typedef struct {
        double **array;
        uint16_t size_row;
        uint16_t size_col;
        double *err;
        double *result;
    } Biarray;
#endif



int math_pow(int base, uint8_t exp);

static double convert(char *ini, char *end, uint8_t flag);

double math_atof(char *ini_number);

int math_atoi(char *ini_number);

static void math_doublecpy(double *dest, double *orig, uint16_t size);

static double *math_calcerr(double *value_xi, double *value_x0, double error, uint16_t iteration);

double *math_gaussJacobi(Biarray *ptr, double error);

double *math_gaussSeidl(Biarray *ptr, double error);

int math_gaussJordan(Biarray *ptr);

Biarray *mem_biArrayAlloc(uint16_t row, uint16_t col);

void mem_memflush(Biarray *ptr);