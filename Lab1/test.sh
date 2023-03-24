#!/bin/bash

for i in {1..4}
do  echo "Running test case $i"
    input_file="example$i.cmm" 
    output_file="example${i}_output.txt" 
    ./parser ./Test/$input_file > ./Test/$output_file 
done