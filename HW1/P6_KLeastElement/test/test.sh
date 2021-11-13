#!/bin/bash

echo ""
echo "$(tput setaf 2; tput bold)Start test: Input/Output $(tput sgr0)"

for i in {151..151};
do
    echo "$(tput setaf 5)Test File: $i.in$(tput sgr0)";


    ./build/main.out < test/data/$i.in ""  > test/data/$i-EST.out; 


    if diff -q test/data/$i-EST.out test/data/$i.out;
    then
        echo "$(tput setaf 2; tput bold)Pass $(tput sgr0)";
    else
        echo "Failed (Compare: EST / Real)"; 
        diff -y test/data/$i-EST.out test/data/$i.out;
    fi
done