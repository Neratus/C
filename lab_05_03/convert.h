#ifndef CONV_H
#define CONV_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define OK 0
#define ERROR_IO -3

int export(char *file_path_in, char *file_path_out);

int import(char *file_path_in, char *file_path_out);

#endif
