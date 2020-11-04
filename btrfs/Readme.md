This folder stores learning of using btrfs.


Distribution: **Ubuntu 20.04**

- Installation: `apt install btrfs-progs`

- Create a Btrfs file system: `mkfs.btrfs /dev/DISK-NAME`

  > Use `lsblk` to get disk name

- Mount: `mount /dev/DISK-NAME /srv`

  > List filesystems: `df -hT`

- Mount the file system at system startup

  ```
  # /etc/fstab
  UUID=UUID-VALUE /srv           btrfs   defaults      0  0
  ```

  > Get block device UUID: `blkid /dev/DISK-NAME`

