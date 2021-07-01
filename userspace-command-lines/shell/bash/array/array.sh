#!/bin/sh


myArray=("one" "two" "three" "four")


echo "Access array with index: ${myArray[0]}"


echo 
echo "Loop through array elements:"
for i in ${myArray[@]}; do
    echo $i
done

echo 
echo "Loop through array indices:"
for i in ${!myArray[@]}; do
    echo $i
done

