#!/bin/sh

while true; do
    sleep 2
    trap 'echo "trap event: 2"; exit' 2
done
