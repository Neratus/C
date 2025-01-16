#!/bin/bash

gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion --coverage -g3 -Wvla -O0 main.c
gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion --coverage -g3 -Wvla -O0 student_bin.c
gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion --coverage -g3 -Wvla -O0 student.c
gcc -c -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion --coverage -g3 -Wvla -O0 convert.c
gcc -o app.exe --coverage -g3 main.o student_bin.o student.o convert.o -lm