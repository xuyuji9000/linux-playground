Q: How to cmpress a directory?

A: 

    tar --create \
    --gzip \
    --verbose \
    --file TARGET.tar.gz \
    ./SOURCE_DIRECTORY
