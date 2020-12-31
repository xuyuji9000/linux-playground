# Introduction

This document is used to document learning of `tput` command.


## Commands

- Get current terminal type[1]: `echo $TERM`

- Print out terminal capabilities[1]: `infocmp $TERM`

- Enable bold and disable bold[4]:

    ``` bash
    bold=$(tput bold)
    normal=$(tput sgr0)
    echo "this is ${bold}bold${normal} but this isn't"
    ```

    outputs

    >this is **bold** but this isn't

# Reference


1. [tput](https://www.linuxcommand.org/lc3_adv_tput.php)

    > This article introduces tput in depth.

2. [ncurses](https://invisible-island.net/ncurses/announce.html)

    > tput is part of ncurses package.


3. [terminfo Directory](https://www.ibm.com/support/knowledgecenter/ssw_aix_72/filesreference/terminfo.html)

    > This document contains terminal capability tables.

4. [How does one output bold text in Bash?](https://stackoverflow.com/questions/2924697/how-does-one-output-bold-text-in-bash#answer-2924755)

    > Here provides an example of printing bold on terminal.
