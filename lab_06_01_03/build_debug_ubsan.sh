#!/bin/bash

clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer  -g3 -Wvla -O0 main.c
clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=undefined -fno-omit-frame-pointer  -g3 -Wvla -O0 products.c
clang -o app.exe -g3 main.o products.o -lm  -fsanitize=undefined
