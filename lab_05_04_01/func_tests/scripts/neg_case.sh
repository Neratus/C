#!/bin/bash

args_file="$2"

prog="./app.exe"

read -r args < "$args_file"

IFS=' ' read -r -a args <<< "$args"

if ! $prog "${args[@]}" > tmp ; then
    exit 0
else
    exit 1
fi
