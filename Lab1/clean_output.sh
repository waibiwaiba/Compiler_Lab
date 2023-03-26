#!/bin/bash

for i in {1..4}
do
    echo "Clean test output $i"
    rm ./Test/example${i}_output.txt
done