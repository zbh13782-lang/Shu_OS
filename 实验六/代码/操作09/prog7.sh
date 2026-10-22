#!/bin/bash
PS3="Choose (1 or 2): "

select item in continue finish
do
    if [ "$item" = "finish" ]
    then
        echo "Finished"
        break
    elif [ "$item" = "continue" ]
    then
        echo "Continue selected"
    else
        echo "Invalid choice"
    fi
done
