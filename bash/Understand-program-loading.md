# Introduction

This document tries to understand how bash script loads and execution happened at the low level.

![execve()](./systemcall-execve.png)

## What does Unix loader do?

1. validation(permission, memory requirements etc.);

2. copying the program image from the disk into main memory;

3. copying the command-line arguments oon the stack;

4. initializing registers(e.g. the stack pointer);

5. jumping to the program entry point(_start).

## Unsolved problmes

- Understand format used for execution on unix-like systems 
  This question for executable script is understanding how script runtime interpret the script

- How the program execution context is setup on Linux ?









# Reference

1. [Loader (computing)](https://en.wikipedia.org/wiki/Loader_(computing))

2. [Understanding the Linux Kernel / Chapter 20 Program Execution ](https://doc.lagout.org/operating%20system%20/linux/Understanding%20Linux%20Kernel.pdf)

3. [Advanced Bash-Scripting Guide](https://tldp.org/LDP/abs/html/)

4. [execve(2) — Linux manual page](https://man7.org/linux/man-pages/man2/execve.2.html)

5. [Unix/Linux Loader Process](https://unix.stackexchange.com/questions/50335/unix-linux-loader-process#answer-50346)
