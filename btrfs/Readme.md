This folder stores learning of using btrfs.



# Prepare btrfs
Distribution: **Ubuntu 20.04**

- Installation: `apt install btrfs-progs`

- Create a Btrfs file system: `mkfs.btrfs /dev/DISK-NAME`

  > Use `lsblk --fs --paths` to get disk name

- Mount: `mount /dev/DISK-NAME /srv`

  > List filesystems: `df -hT`

- Mount the file system at system startup

  ```
  # /etc/fstab
  UUID=UUID-VALUE /srv           btrfs   defaults      0  0
  ```

  > Get block device UUID: `blkid /dev/DISK-NAME`

# Try out transparent compression[2]


- Test dataset[1]

- Compression

  > `btrfs filesystem defrag -v -r -f -czlib dir/`

  > How to know compressed file size[3]

# Reference

1. [Property Listings for 5 South American Countries](https://www.kaggle.com/rmjacobsen/property-listings-for-5-south-american-countries?select=uy_properties.csv)

2. [Arch Linux / Btrfs / Compression](https://wiki.archlinux.org/index.php/btrfs#Compression)

3. [Btrfs / Compression / How_can_I_determine_compressed_size_of_a_file](https://btrfs.wiki.kernel.org/index.php/Compression#How_can_I_determine_compressed_size_of_a_file.3F)
