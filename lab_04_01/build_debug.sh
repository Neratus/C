#!/bin/bash

gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion --coverage -g3 -Wvla -O0 main.c
gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion --coverage -g3 -Wvla -O0 my_str.c
gcc -o app.exe --coverage -g3 main.o my_str.o -lm