#!/bin/bash

in_file=$1
cd ..
cd ..
prog="./app.exe"

if ! $prog < "$in_file" > tmp; then
    exit 0
else
    exit 1
fi