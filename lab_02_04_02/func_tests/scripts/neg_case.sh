#!/bin/bash

in_file=$1
out_file=$2
cd ..
cd ..
prog="./app.exe"

"$prog" < "$in_file" > tmp
return_code=$?
if [ $return_code -eq 100 ]; then
    if ./func_tests/scripts/comparator.sh tmp "$out_file"; then
        exit 0
    else
        exit 1
    fi
else
    if [ $return_code -ne 0 ]; then
        exit 0
    else
        exit 1
    fi
fi