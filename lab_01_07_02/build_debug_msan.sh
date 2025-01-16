#!/bin/bash

clang -c -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer  --coverage -g3 -Wvla -O0 main.c
clang -o app.exe -g3 main.o  --coverage -lm -fsanitize=memory