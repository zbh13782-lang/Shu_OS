#!/bin/bash
echo "HOME=$HOME"
echo "PATH=$PATH"

if [ $# -eq 0 ]
then
    echo "Usage: $0 file ..."
    exit 1
fi

for file in "$@"
do
    if [ -e "$file" ]
    then
        ls -ld -- "$file"
    else
        echo "$file: does not exist"
    fi
done
