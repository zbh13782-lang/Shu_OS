#!/bin/bash
a=10
b=20
file="prog1.sh"
dir="."

if [ "$a" -lt "$b" ]
then
    echo "$a is less than $b"
else
    echo "$a is not less than $b"
fi

if [ -d "$dir" ]
then
    echo "$dir is a directory"
fi
if [ -f "$file" ]
then
    echo "$file is a regular file"
fi
if [ -r "$file" ]
then
    echo "$file is readable"
fi
if [ -w "$file" ]
then
    echo "$file is writable"
fi
if [ -x "$file" ]
then
    echo "$file is executable"
fi
