

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
