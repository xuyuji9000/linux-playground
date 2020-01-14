#!/bin/sh

numbers=(1 2 4 8 16 32 64 128)


for i in ${!numbers[@]}; do

    echo ${numbers[$i]}
done