This file documents `cscope` usage with vim.



- Prepare *cscope.files*

``` shell
find . -type f -iname *.c -o -iname *.h > cscope.files
```

- Generate database 

``` shell
cscope -b -q
```

- Add database 

``` vim
:cs add cscope.out
```