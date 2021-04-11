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

- Prepare ctags on Macos

``` bash
brew install --verbose --debug ctags 

# Move into the target directory

ctag --recurse .
```

- Ctag shortcuts

    Go to function definition: `Control + ]`

    Go back to function instance: `Control + T`

    Open function definition in a slit: `Control + W, Control + ]` 

    Navigate between slits: `Control + W, Control + (arrow key)`

- Search for specific file 

```
# use within vim
:Explore **/[pattern]
```


# Reference

1. [Vim: error reading input](https://stackoverflow.com/questions/40319486/vim-error-reading-input#answer-40321262)
