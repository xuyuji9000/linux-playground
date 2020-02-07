### Commands

- create hard link: `ln original.txt hard-link.txt`

- Create symbolic link: `ln -s original.txt soft-link.txt`

- Check inode: `stat -f %i original.txt`

### FAQ

Q: What is the difference between symbolic link and hard link?

A: Symbolic link points to an exiting file, instead of directly point to hard drive. While 2 hard links points directly to the hard drive and share the inode.
