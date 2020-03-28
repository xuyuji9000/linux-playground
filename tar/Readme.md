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
