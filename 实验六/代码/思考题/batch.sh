#!/bin/bash
echo "Shell file line counts" > batch_result.txt

for file in *.sh
do
    if [ -f "$file" ]
    then
        wc -l -- "$file" >> batch_result.txt
    fi
done

cat batch_result.txt
