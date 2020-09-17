# Introduction

This document tries to understand how executable program(specifically bash script) loads.

![execve()](./systemcall-execve.png)

## Steps involed in executing a bash script 

1. Shell itself is a process, new command execute within the context of shell

2. Format interpretation based on ELF format

3. fork() get a PID with everything else stays the same

4. execve() keeps the new PID, clean the other state up(stack, program user space, etc)

5. Kernel hand control back to user space program


## ELF format 

ELF's first 4 bytes is magic number.

Bash is represented by file signature `#!`.

## Unsolved problmes

- Understand ELF format

  - How does this format support loading into memory?

- What does execution context contains?

- How execution context is setup based on executable file?

  - How process memory is initiated based on ELF format?

- What happens with interactive shell initiation itself? Like how the environment variables is first iniated, etc.



# Reference

1. [Loader (computing)](https://en.wikipedia.org/wiki/Loader_(computing))

2. [Understanding the Linux Kernel / Chapter 20 Program Execution ](https://doc.lagout.org/operating%20system%20/linux/Understanding%20Linux%20Kernel.pdf)

3. [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/)

4. [execve(2) — Linux manual page](https://man7.org/linux/man-pages/man2/execve.2.html)

5. [Unix/Linux Loader Process](https://unix.stackexchange.com/questions/50335/unix-linux-loader-process#answer-50346)

6. [Executable and Linkable Format](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_layout)

7. [List of file signatures](https://en.wikipedia.org/wiki/List_of_file_signatures)

8. [Reverse Engineering | ELF File Format | Beginners](https://www.youtube.com/watch?v=OBDuoqyZ4UA&t=66s)

9. [Understanding the Linux Kernel / Chapter 3 Processes / Create Processes](https://doc.lagout.org/operating%20system%20/linux/Understanding%20Linux%20Kernel.pdf)

10. [Shebang (Unix)](https://en.wikipedia.org/wiki/Shebang_(Unix))

11. [Understanding the Linux Kernel / Chapter 9 Process Address Space ](https://doc.lagout.org/operating%20system%20/linux/Understanding%20Linux%20Kernel.pdf)
