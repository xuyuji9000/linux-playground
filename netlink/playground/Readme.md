This folder contains an example using netlink feature to communicate with the kernel.

- Build

``` shell
gcc -o main main.c
```

- Build with debug info


``` shell
gcc -Wall -g ./main.c
```

- Package source code

``` shell
tar -cf src.tar ./src
```

- Extract source code 


``` shell
tar -x -v -f ./src.tar
```

- Generate tag file

``` shell
ctags --recurse .
```

# Reference

1. [Linux Netlink as an IP Services Protocol](https://tools.ietf.org/html/rfc3549)

2. [wireguard-tools](https://git.zx2c4.com/wireguard-tools/about/)

    > This example's source code heavily referenced wireguard-tools' codebase.
