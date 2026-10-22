#!/bin/bash
display_month()
{
    case "$1" in
        1|01) echo "January" ;;
        2|02) echo "February" ;;
        3|03) echo "March" ;;
        4|04) echo "April" ;;
        5|05) echo "May" ;;
        6|06) echo "June" ;;
        7|07) echo "July" ;;
        8|08) echo "August" ;;
        9|09) echo "September" ;;
        10) echo "October" ;;
        11) echo "November" ;;
        12) echo "December" ;;
        *) echo "Invalid month" ;;
    esac
}

display_month 9
display_month 10
display_month 14
