This document introduce `if-statement` examples.


- first example

    ``` bash
    if [ -z "${VARIABLE_NAME}" ];
    then 
      #logic here
    fi
    ```

    > `${VARIABLE_NAME}` needs to be wrapped inside **double quote**, so when `${VARIABLE_NAME}` value is empty, there will still be an empty string.

