#!/bin/bash

# 删除所有由上一个脚本生成的${filename}_output.txt文件
for file in ../Test/*.ir
do
  echo "${file} deleted."
  rm "$file"
done