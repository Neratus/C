#!/bin/bash

GREEN=$'\e[1;32m'
RED=$'\e[1;31m'
NC=$'\e[1;0m'

num_fails=0

files=(./func_tests/data/pos_[0-9][0-9]_args.txt)
if [ "$1" != "-s" ]; then
    echo "Pos tests"
fi
for input in "${files[@]}"
do
    if [ "$input" == "./func_tests/data/pos_[0-9][0-9]_args.txt" ]; then
        if [ "$1" != "-s" ]; then
            echo "-"
        fi
        break
    fi
    curr_num=$(echo "$input" | grep -o '[0-9][0-9]')
    in_file=./func_tests/data/pos_"$curr_num"_in.txt
    out_file=./func_tests/data/pos_"$curr_num"_out.txt
    "./app.exe" import "$in_file" bin_in_tmp
    result=$?
    if [[ $result = 0 ]]; then
        if ./func_tests/scripts/pos_case.sh "$in_file" "$out_file" "$input"; then
            if [ "$1" != "-s" ]; then
                echo "pos_test_$curr_num$GREEN passed $NC"
            fi
        else
            if [ "$1" != "-s" ]; then
                echo "pos_test_$curr_num$RED error $NC"
            fi
            num_fails=$((num_fails + 1))
        fi
    else
        echo "pos_test_$curr_num$RED Build failed $NC"
        num_fails=$((num_fails + 1))
    fi
done

files=(./func_tests/data/neg_[0-9][0-9]_args.txt)
if [ "$1" != "-s" ]; then
    echo
    echo "Neg tests"
fi
for input in "${files[@]}"
do
    if [ "$input" == "./func_tests/data/neg_[0-9][0-9]_args.txt" ]; then
        if [ "$1" != "-s" ]; then
            echo "-"
        fi
        break
    fi
    curr_num=$(echo "$input" | grep -o '[0-9][0-9]')
    in_file=./func_tests/data/neg_"$curr_num"_in.txt
    out_file=./func_tests/data/neg_"$curr_num"_out.txt
    "./app.exe" import "$in_file" bin_in_tmp > tmp
    result=$?
    if [[ $result = 0 ]]; then
        if ./func_tests/scripts/neg_case.sh "$in_file" "$input"; then
            if [ "$1" != "-s" ]; then
                echo "neg_test_$curr_num$GREEN passed $NC"
            fi
        else
            if [ "$1" != "-s" ]; then
                echo "neg_test_$curr_num$RED error $NC"
            fi
            num_fails=$((num_fails + 1))
        fi
    else
        echo "neg_test_$curr_num$GREEN passed $NC"
    fi
done

if [ "$1" != "-s" ]; then
    echo
    echo "Error num = ""$num_fails"
fi

rm -f tmp
rm -f bin_in_tmp
rm -f bin_out
exit $num_fails