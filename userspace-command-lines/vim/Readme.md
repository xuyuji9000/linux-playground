This folder is used to vi examples.


- Manipulate file with here document:

    ``` bash
    vi test.txt <<INPUT
    i
    This is line 1
    ^[
    ZZ
    INPUT
    ```

    > `^[` is generated with `Control - v`, `Esc`[1]

    > Difference between `ZZ` and `:wq` :
    > - `ZZ` only update timestamp when there is change to file
    > - `:wq` updates timestamp regardless

- Search for specific file 

```
# use within vim
:Explore **/[pattern]
```

- [ctags](./ctags.md)

# Reference

1. [Vim: error reading input](https://stackoverflow.com/questions/40319486/vim-error-reading-input#answer-40321262)
