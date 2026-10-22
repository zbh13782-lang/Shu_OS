#!/bin/bash
mkdir -p backup9

for file in *.sh
do
    if [ -f "$file" ]
    then
        cp -v "$file" backup9/
    fi
done
