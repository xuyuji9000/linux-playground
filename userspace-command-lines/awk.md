- Sum numbers

```
cat <<EOF > numbers.txt
2
2
3
EOF

awk '{s+=$1} END {printf s}' numbers.txt
```
