#!/bin/bash

sizes=$(cat ../config/sizes_of_arr.txt)
names="main_index main_pointer_index main_pointer"
count=20

if [ ! -z "$1" ]; then
    count="$1"
fi

if [ ! -z "$2" ]; then
    sizes="$2"
fi


for i in $(seq "$count"); do
    for name in $names; do
        for size in $sizes; do
            ../apps/"$name"_out_"$size".exe >> ../data/"${name}"_out_"${size}".txt
        done
    done
done

for name in $names; do
    for size in $sizes; do
        ../apps/"$name"_in_"$size".exe >> ../data/"${name}"_in_"${size}".txt
    done
done

