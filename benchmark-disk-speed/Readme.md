

command for benchmarking hard disk: `dd if=/dev/zero of=/root/disk-speed.img bs=1024k count=1024 oflag=dsync`


|        | QingCloud system disk  | Aliyun high performance  | Aliyun SSD  | Azure Premium SSD | AWS general purpose SSD |
|--------|------------------------|--------------------------|-------------|-------------------|-------------------------|
|  SPEED | 40.1 MB/s              | 108 MB/s                 | 134 MB/s    | 25.1 MB/s         | 67.9 MB/s               |
