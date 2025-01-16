#!/bin/bash

file_in="$1"
args_file="$2"

prog="./app.exe"

read -r args < "$args_file"

IFS=' ' read -r -a args <<< "$args_file"

if ! $prog "${args[@]}"< "$file_in" > tmp ; then
    exit 0
else
    exit 1
fi
