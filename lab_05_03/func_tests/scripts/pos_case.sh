#!/bin/bash

out_file=$2
args_file=$3

prog="./app.exe"

read -r args < "$args_file"

IFS=' ' read -r -a args <<< "$args"
 
if [[ "${args[0]}" == "p" ]] ; then
    if $prog "${args[@]}" > tmp && ./func_tests/scripts/comparator.sh tmp "$out_file" ; then
        exit 0
    else
        exit 1
    fi
elif [[ "${args[0]}" == "s" ]] ; then
    if $prog "${args[@]}"; then
        $prog export bin_in_tmp tmp
        result=$?
        if [[ $result != 0 ]]; then
            exit 1
        fi
        if ./func_tests/scripts/comparator.sh tmp "$out_file" ; then
            exit 0
        else
            exit 1
        fi
    else
        exit 1
    fi
fi
exit 1