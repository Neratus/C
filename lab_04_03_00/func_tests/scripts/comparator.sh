#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Использование: comparator.sh файл1 файл2"
  exit 1
fi

file1=$1
file2=$2
word="Result: "
get_string() {
  awk -v pattern="$1" '{if (index($0, pattern) != 0) found=1; if (found) print}' "$2"
}

f1=$(get_string "$word" "$file1")
f2=$(get_string "$word" "$file2")

if [ "$f1" != "$f2" ]; then
  exit 1
fi
  exit 0