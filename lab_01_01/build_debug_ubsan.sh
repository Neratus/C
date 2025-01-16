#!/bin/bash

clang -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer  --coverage -g3 -Wvla -O0 main.c
clang -o app.exe -g3 main.o -lm  --coverage -fsanitize=undefined