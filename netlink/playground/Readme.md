This folder contains an example using netlink feature to communicate with the kernel, and list network interface names.


# Commands

- Build

``` shell
gcc -o main main.c
```

- Build with debug info


``` shell
gcc -Wall -g ./main.c
```

- Generate tag file

``` shell
ctags --recurse .
```

# Reference

1. [Linux Netlink as an IP Services Protocol](https://tools.ietf.org/html/rfc3549)

2. [wireguard-tools](https://git.zx2c4.com/wireguard-tools/about/)

    > This example's source code heavily referenced wireguard-tools' codebase.
