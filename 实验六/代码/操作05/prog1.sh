#!/bin/bash
read -r -p "Please input your name: " name

if [ -z "$name" ]
then
    echo "Name not provided"
else
    echo "Your name is $name"
fi
