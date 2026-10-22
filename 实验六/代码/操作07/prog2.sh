#!/bin/bash
read -r -p "Input string 1: " str1
read -r -p "Input string 2: " str2

if [ "$str1" = "$str2" ]
then
    echo "Strings are equal"
else
    echo "Strings are different"
fi

if [ -n "$str1" ]
then
    echo "str1 is not empty"
else
    echo "str1 is empty"
fi

if [ -z "$str2" ]
then
    echo "str2 is empty"
else
    echo "str2 is not empty"
fi
