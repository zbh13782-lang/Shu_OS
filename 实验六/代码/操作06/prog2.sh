#!/bin/bash
str1="hello"
str2="world"

if [ "$str1" = "$str2" ]
then
    echo "Strings are equal"
else
    echo "Strings are different"
fi

if [ -n "$str1" ]
then
    echo "str1 is not empty"
fi

if [ -z "$str2" ]
then
    echo "str2 is empty"
else
    echo "str2 is not empty"
fi
