#!/bin/sh


VAR="This displays with \nextra spaces."

echo ${VAR} | while read line; do
    echo $line
done
