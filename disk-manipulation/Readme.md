This document is about how to use Logical Volume Management tools.

- Installation[2]: `yum install lvm2`


lsblk

- List block devices: `lsblk`[1]

lvmdiskscan

- List disk devices: `lvmdiskscan`

## Create a logic volume from ground up[3]

1. Initialize physical volume: `pvcreate /dev/DEVICE_NAME`

2. Create volume group: `vgcreate vg01 /dev/DEVICE_NAME`

3. Create logical volume: `lvcreate --size 5G --name lvol01 vg01`

# Reference

1. [6 Different Ways to List Hard Drives in Linux](https://linuxhandbook.com/linux-list-disks/)

2. [How to Install and Configure LVM on CentOS 7](https://linuxhint.com/install_lvm_centos7/)

3. [Beginner’s Guide to LVM (Logical Volume Management)](https://www.thegeekdiary.com/redhat-centos-a-beginners-guide-to-lvm-logical-volume-manager/)
