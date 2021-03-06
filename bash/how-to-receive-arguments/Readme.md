- Validate if variable is empty[2]


    ``` bash
    if [ -z "${ARGUMENT}" ] ; then 
        echo "\${ARGUMENT} is empty"
        exit 1
    fi
    ```

    > `-z` True if the length of string is zero

    > `${ARGUMENT}` needs to be wrapped inside **double quote**, so when `${ARGUMENT}` value is empty, there will still be an empty string.


- Absract `die` function[4]

    ``` bash
    die() {
        echo "$@"
        exit 1
    }
    ```

    > `$@`[5] holds all positional arguments passsed to the function

- Arguement validation in one line 

    ``` bash
    die() {
        echo "$@"
        exit 1
    }

    test -z "${ARGUMENT}" && die "\$ARGUMENT is empty"
    ```

    > `test`[3] evaluates a conditional expression

    > `test -z String` is True if the length of String is zero


# Reference 

1. [How do I parse command line arguments in Bash?](https://stackoverflow.com/questions/192249/how-do-i-parse-command-line-arguments-in-bash)

2. [Bash Shell Find Out If a Variable Is Empty Or Not](https://www.cyberciti.biz/faq/unix-linux-bash-script-check-if-variable-is-empty/)

3. [test](https://ss64.com/bash/test.html)

4. [Validating parameters to a Bash script](https://stackoverflow.com/questions/699576/validating-parameters-to-a-bash-script#answer-699613)

5. [Bash Functions](https://linuxize.com/post/bash-functions/#passing-arguments-to-bash-functions)
