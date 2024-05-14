#!/bin/bash

sizes=$(cat ../config/sizes_of_arr.txt)


cd ../src_1 || exit
for FILE in main*.c; do
  for size in $sizes; do
      gcc -lm \
          -O0 \
          -DNMAX="${size}"\
          "$FILE" -o "../apps/${FILE%.c}_in_${size}.exe"
  done
done

cd ../src_2 || exit
for FILE in ./main*.c; do
  for size in $sizes; do
      gcc -lm \
          -O0 \
          -DNMAX="${size}"\
          "$FILE" -o "../apps/${FILE%.c}_out_${size}.exe"
  done
done
