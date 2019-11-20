
## Inherited Design 

Operating system writes to buffer to improve performance.

## Consequence of Inherited Design

During a sudden system crash or power failure, all the changes made in memory only will be lost, potentially leave the file system corrupted.

## Specification

Periodically copy all the changes reflected in the memory to the disk.

## Implementation

Journaling reserve a contiguous portion of the disk, this way is thousand times faster than seeking dirty data location all around the disk.

## Trade off of the Implementation

- Complicate reading for read from disk,  everytime read from disk needs to check the journal to see if any changes to apply
- Total time spent to writing is more, since we are making 2 writes instead of 1.


## Questions

1. What was it like when there is no journaling file system? How the dirty data in memory goes into the disk ?

2. Why use circular log / circular buffer / ring buffer as the data structure?



## Reference 

1. [Journaling](https://www.youtube.com/watch?v=jey0BEqCEkM)

2. [Anatomy of Linux journaling file systems](https://www.ibm.com/developerworks/library/l-journaling-filesystems/index.html)
