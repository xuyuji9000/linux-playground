- pass input into quoted argument

``` shell
echo "Hello World" | xargs -I{} echo "{}"
```

