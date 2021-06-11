#!/bin/sh

# This script 
# - prompt user with an introduction
# - expect a input


while :
do
    echo "Current directory: `pwd`"
    echo "Type in the directory you want to list: "

    read line 
    eval "ls -1 $line"

    echo ""
done

exit 0

