#!/bin/bash

while getopts ":hw" opt; do
    case ${opt} in
        h ) 
            echo "Hello"
            ;;
        w )
            echo "World"
            ;;
        \? )
            echo "Usage: cmd [-h] [-w]"
            ;;
    esac
done
