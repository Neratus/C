#ifndef MY_SNPRINTF
#define MY_SNPRINTF

#include <stdlib.h>

#define BUF_LEN sizeof(size_t) * 8

int my_snprintf(char *s, size_t n, const char *format, ...);

#endif 
