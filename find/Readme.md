This document contains examples related to `find`[2] command.


- List file with specific extensions[1]

  `find . -iname *.md`

- Execute command on found files

  `find . -iname *.md  -exec ls -lh {} \;`

  > `{}` is replaced by the current filename being processed
  
  > `\;` is indicating the end of the command executed on the filename


# Reference

1. [How to use find command to find all files with extensions from list?](https://stackoverflow.com/questions/2621513/how-to-use-find-command-to-find-all-files-with-extensions-from-list)

2. [find(1) — Linux manual page](https://man7.org/linux/man-pages/man1/find.1.html)
