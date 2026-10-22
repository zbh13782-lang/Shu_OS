#!/bin/bash
read -r -p "Input file path: " file

if [ ! -e "$file" ]; then
    echo "Path does not exist"
    exit 1
fi

if [ -d "$file" ]; then
    echo "Type: directory"
elif [ -f "$file" ]; then
    echo "Type: regular file"
else
    echo "Type: other"
fi

if [ -r "$file" ]; then
    echo "Readable: yes"
else
    echo "Readable: no"
fi
if [ -w "$file" ]; then
    echo "Writable: yes"
else
    echo "Writable: no"
fi
if [ -x "$file" ]; then
    echo "Executable/searchable: yes"
else
    echo "Executable/searchable: no"
fi
