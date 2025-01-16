#!/bin/bash

clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer  -g3 -Wvla -O0 main.c
clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer  -g3 -Wvla -O0 student_bin.c
clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer  -g3 -Wvla -O0 student.c
clang -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -fsanitize=memory -fPIE -fno-omit-frame-pointer  -g3 -Wvla -O0 convert.c
clang -o app.exe -g3 main.o student_bin.o student.o convert.o -lm -fsanitize=memory