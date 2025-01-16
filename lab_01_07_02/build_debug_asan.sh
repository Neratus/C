#!/bin/bash

clang -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=address -fno-omit-frame-pointer -g3 -Wvla --coverage -O0 main.c
clang -o app.exe -g3 --coverage main.o -lm -fsanitize=address