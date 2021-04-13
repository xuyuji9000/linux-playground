This fille documents ctags usage with vim.

- Prepare ctags on Macos

``` bash
brew install --verbose --debug ctags 

# Move into the target directory

ctags --recurse .
```

- Ctag shortcuts

    Go to function definition: `Control + ]`

    Go back to function instance: `Control + T`

    Open function definition in a slit: `Control + W, Control + ]` 

    Navigate between slits: `Control + W, Control + (arrow key)`