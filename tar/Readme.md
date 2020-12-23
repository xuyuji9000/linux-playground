# Introduction

`tar` is a computer software utility for collecting many files into one archive file.

## Options

- `-p`

    Preserve permissions.

- `-c`

    Create new file.

- `-f`

    Allows to specify the filename of the archive.

## Examples

- Create a tar file for a directory

    `tar -pcf TAR_FILE.tar SOURCE_DIRECTORY`

    > `.FILENAME` ignored files are archived as well.

# Q&A

Q: What is the advantage of [archive file](https://en.wikipedia.org/wiki/Archive_file)?

A: Archive files are paticularly useful that they store file system data and metadata within the contents of a particular file, and thus can be stored on systems or send over channels that do not support the file system in question, only file contents.

Q: How to cmpress a directory?

A: 

    # Long version
    tar --create \
    --gzip \
    --verbose \
    --file TARGET.tar.gz \
    ./SOURCE_DIRECTORY

    # Short Version
    tar -czvf TARGET.tar.gz ./SOURCE_DIRECTORY

Q: How to list contents from a tarball?

A: 

    tar -tvf ./ORIGINAL.tar.gz
