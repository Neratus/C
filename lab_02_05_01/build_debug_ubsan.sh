#!/bin/bash

clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer  -g3 -Wvla -O0 main.c
clang -o app.exe -g3 main.o -lm  -fsanitize=undefined