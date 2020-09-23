This document is about how to use Logical Volume Management tools.

- Installation[2]: `yum install lvm2`


lsblk

- List block devices: `lsblk`[1]

lvmdiskscan

- List disk devices: `lvmdiskscan`

## Create file system on top of logical volume[3]

1. Initialize physical volume: `pvcreate /dev/DEVICE_NAME`

2. Create volume group: `vgcreate vg01 /dev/DEVICE_NAME`

3. Create logical volume: `lvcreate --size 5G --name lvol01 vg01`

4. Create a ext4 file system: `mkfs.ext4 /dev/vg01/lvol01`

5. Mount:

    ``` bash
    mkdir /data01
    mount /dev/vg01/lvol01 /data01
    ```
6. Add an entry to `/etc/fstab` for automatic mouting

    ```
    # vi /etc/fstab
    UUID=PoWVAi-pwGx-jzhc-VdTr-jVn0-GQOt-eEWInz /data01                       ext4	defaults	0 0
    /dev/vg01/lvol01	/data01			ext4	defaults	0 0
    ```

    > Get UUID information `blkid /dev/vg01/lvol01`


# Reference

1. [6 Different Ways to List Hard Drives in Linux](https://linuxhandbook.com/linux-list-disks/)

2. [How to Install and Configure LVM on CentOS 7](https://linuxhint.com/install_lvm_centos7/)

3. [Beginner’s Guide to LVM (Logical Volume Management)](https://www.thegeekdiary.com/redhat-centos-a-beginners-guide-to-lvm-logical-volume-manager/)
