#!/bin/bash

clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer  -g3 -Wvla -O0 main.c
clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer  -g3 -Wvla -O0 matrix_io.c
clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer  -g3 -Wvla -O0 func.c
clang -o app.exe -g3 main.o func.o  matrix_io.o -lm -fsanitize=memory