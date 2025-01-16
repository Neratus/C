#ifndef MYSTR_H
#define MYSTR_H

#include <stdio.h>

const char *my_strpbrk(const char *str, const char *sym);

size_t my_strspn(const char *str, const char *sym);

size_t my_strcspn(const char *str, const char *sym);

const char *my_strchr(const char *str, int ch);

const char *my_strrchr(const char *str, int ch);

#endif
