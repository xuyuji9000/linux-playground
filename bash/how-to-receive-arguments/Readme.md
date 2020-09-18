- Validate if variable is empty[2]


    ``` bash
    if test -z "${ARGUMENT}"
    then 
    echo "\$ARGUMENT is empty"
    exit 1
    fi
    ```


# Reference 

1. [How do I parse command line arguments in Bash?](https://stackoverflow.com/questions/192249/how-do-i-parse-command-line-arguments-in-bash)

2. [Bash Shell Find Out If a Variable Is Empty Or Not](https://www.cyberciti.biz/faq/unix-linux-bash-script-check-if-variable-is-empty/)
