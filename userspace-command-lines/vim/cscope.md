This file documents `cscope` usage with vim.



- Prepare *cscope.files*

``` shell
find . -type f -iname *.c -o -iname *.h > cscope.files
```

- Generate database 

``` shell
cscope -b -i cscope.files
```

- Add database 

``` vim
:cs add cscope.out
```