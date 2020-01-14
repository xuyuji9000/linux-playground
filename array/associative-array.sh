#!/usr/bin/env bash

# associative array is quite different on different versions of bash

declare -A aa
aa[hello]=world



for i in "${!aa[@]}"
do
  echo "key  : $i"
  echo "value: ${aa[$i]}"
done
