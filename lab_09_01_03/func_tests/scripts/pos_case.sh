#!/bin/bash

file_in=$1
out_file=$2
args_file=$3

if [ "$3" == "--valgrind" ]; then
    prog="valgrind --leak-check=yes -q ./app.exe"
else
    prog="./app.exe"
fi

read -r args < "$args_file"

IFS=' ' read -r -a args <<< "$args"

if $prog "${args[@]}" < "$file_in" > tmp && ./func_tests/scripts/comparator.sh tmp "$out_file" ; then
    exit 0
else
    exit 1
fi
