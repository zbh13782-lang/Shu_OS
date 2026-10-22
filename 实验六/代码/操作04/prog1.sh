#!/bin/bash
echo "Parameter count: $#"
echo "Program name: $0"

if [ $# -eq 0 ]
then
    echo "Name not provided"
else
    n=1
    for arg in "$@"
    do
        echo "Parameter $n: $arg"
        n=$((n + 1))
    done
fi
