#!/bin/bash
ls -l > filedir.txt
mkdir -p testdir2

for file in $(ls *.c)
do
    cp "$file" testdir2/
    chmod a-r "testdir2/$file"
done

ls -l testdir2 >> filedir.txt
id >> filedir.txt
more -5 filedir.txt
