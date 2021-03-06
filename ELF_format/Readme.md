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

4. [Understanding the ELF File Format](https://linuxhint.com/understanding_elf_file_format/)

    > This fie described the benefits of standardizing binary file format with  ELF format.

5. [In-depth: ELF - The Extensible & Linkable Format](https://www.youtube.com/watch?v=nC1U1LJQL8o)

    > This video provides a structured introduction of ELF


6. [Application binary interface](https://en.wikipedia.org/wiki/Application_binary_interface)

    > ELF format is first published in the specification for the *application binary interface*(ABI) of Unix 
