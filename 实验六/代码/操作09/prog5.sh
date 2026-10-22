#!/bin/bash
i=1
sum=0

while [ "$i" -le 10 ]
do
    sum=$((sum + i * 2))
    i=$((i + 1))
done

echo "Result: $sum"
