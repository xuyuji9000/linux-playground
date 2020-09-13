#!/bin/bash

COMMAND="ls -lrt"
eval $COMMAND

a=10
b=a
c='$'$b
echo $c

eval c='$'$b
echo $c
