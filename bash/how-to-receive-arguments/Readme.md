- Validate if variable is empty[2]


    ``` bash
    if test -z "${ARGUMENT}"
    then 
    echo "\$ARGUMENT is empty"
    exit 1
    fi
    ```

    > `test`[3] evaluates a conditional expression

    > `test -z String` is True if the length of String is zero


# Reference 

1. [How do I parse command line arguments in Bash?](https://stackoverflow.com/questions/192249/how-do-i-parse-command-line-arguments-in-bash)

2. [Bash Shell Find Out If a Variable Is Empty Or Not](https://www.cyberciti.biz/faq/unix-linux-bash-script-check-if-variable-is-empty/)

3. [test](https://ss64.com/bash/test.html)