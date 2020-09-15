# Introduction

This document is for accumulating basic ELF format related definition and commands.

## Prepare working environment

1. Start container

    `docker run -it centos:8`

2. Install dependencies

    ```
    # for xxd command
    yum install vim-common

    yum install gcc

    # for better syntax highlight
    yum install vim
    ```
3. Build testing program

``` c
// File name: main.c
// Build command: gcc ./main.c -o main
#include <stdio.h>

int main() 
{
    printf("Hello World!\n");
    return 0;
}
```




## Commands


- Display program in hexadecimal: `xxd -l 64 ./main`

- List symbol table: `readelf --symbols ./main`

- Display ELF header in a more readable way: `readelf -h ./main`


# Refernece

1. [Executable and Linkable Format](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)

2. [Reverse Engineering | ELF File Format | Beginners](https://www.youtube.com/watch?v=OBDuoqyZ4UA)

3. [Mach-O](https://en.wikipedia.org/wiki/Mach-O)

    MacOS is using its own object format `Mach-O`
