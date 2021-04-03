This file is used to document the learning of building Linux kernel.


- Distribution: Centos 8

- Build machine spec: 4 vCPU, 16G memory

# Steps

1. Prepare machine

    > Using alicloud machine for now, cause it provides expiration feature.

2. Prepare dependencies

```
dnf group install "Development Tools"
dnf install ncurses-devel
dnf install elfutils-libelf-devel
dnf install openssl-devel

# prepare 
dnf config-manager --set-enabled PowerTools
dnf install dwarves
```


3. Move to `/tmp` for execution

4. Get the source from [kernel.org](https://www.kernel.org/)

5. [Verify](https://www.kernel.org/category/signatures.html) the source

6. Extract source

7. Copy config file from the current system

```
# Get kernel release info
KERNEL_RRELEASE=`uname -r`

cp -v /boot/config-${KERNEL_RRELEASE} .config
```

8. Comment `CONFIG_SYSTEM_TRUSTED_KEYS="certs/rhel.pem"`

    > This is private key used by RedHat to sign off the kernel modules

    > I don't have it

9. Select feature 

```
make menuconfig
```



9. Build

``` bash
# Build inside a tmux session
yum install tmux
tmux new -s kernel

make rpm-pkg
```

