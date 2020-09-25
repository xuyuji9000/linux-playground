This document introduce `if-statement` examples.


- first example

    ``` bash
    if [ -z "${VARIABLE_NAME}" ];
    then 
      #logic here
    fi
    ```

    > `-z` True if the length of string is zero

    > `${VARIABLE_NAME}` needs to be wrapped inside **double quote**, so when `${VARIABLE_NAME}` value is empty, there will still be an empty string.

