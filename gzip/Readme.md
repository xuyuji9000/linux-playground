Q: How to compress a file?

A: 

    gzip --stdout ORIGINAL.txt > TARGET.txt.gz

Q: How to keep original compression file after decompression?

A: 

    gunzip --stdout --keep TARGET.txt.gz > ORIGINAL.txt
