#!/bin/bash

# plus
x=5
y=10
ans=$(( x + y ))
echo "$x + $y = $ans"

# minus
echo $(( 20 + 5 ))

# division
echo $(( 20 / 5))

# multiplication
echo $(( 20 * 5))

# post increment
x=5
echo $(( x++ ))
echo $(( x++ ))

# post decrement
x=5
echo $(( x-- ))
echo $(( x-- ))

# exponentiation
x=2
y=3
echo $((x**y))
