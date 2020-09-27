This document provide example for singal and trap.


- Send signal to a running process[1]

    ``` bash
    kill -SIGNAL PROCESS_ID
    ```

- Trap a signal

    ``` bash
    trap "command" SIGNAL
    ```

    > [exmaple](./trap.sh)



# Reference

1. [Unix / Linux - Signals and Traps](https://www.tutorialspoint.com/unix/unix-signals-traps.htm)
