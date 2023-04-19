#!/bin/bash

# 打印.cmm文件和对应的output.txt文件
for file in $(ls ../Test/*.cmm | sort -V); do
  # echo "$file"
  echo "[$file]"
  cat "$file"
  filename=$(basename "$file" .cmm)
  echo "[${filename}_output.txt]"
  # echo "../Test/${filename}_output.txt"
  cat "../Test/${filename}_output.txt"
  echo "------------------------------------"
done