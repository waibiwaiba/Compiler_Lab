#!/bin/bash

# 运行parser程序分析Test文件夹下的所有.cmm文件，并将输出结果重定向至对应的_output.txt文件中
for file in ../Test/*.cmm
do
  echo "testing $file"
  filename=$(basename "$file" .cmm)
  # echo "../Test/${filename}_output.txt"
  ./parser "$file" "../Test/${filename}.ir"
done