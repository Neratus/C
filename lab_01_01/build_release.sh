#!/bin/bash

gcc -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -Wvla -O0 main.c
gcc -o app.exe main.o -lm