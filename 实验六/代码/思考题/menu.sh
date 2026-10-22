#!/bin/bash
PS3="Choose (1-4): "

select item in User Environment System Exit
do
    case "$item" in
        User)
            id
            ;;
        Environment)
            echo "HOME=$HOME"
            echo "SHELL=$SHELL"
            echo "PATH=$PATH"
            ;;
        System)
            uname -a
            ;;
        Exit)
            echo "Bye"
            break
            ;;
        *)
            echo "Invalid choice"
            ;;
    esac
done
