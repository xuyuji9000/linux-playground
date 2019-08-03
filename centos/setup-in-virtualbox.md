1. Download centos

2. Setup network as onboot

``` bash
# /etc/sysconfig/network-scripts/ifcfg-eth0
DEVICE=eth0  
BOOTPROTO=dhcp  
ONBOOT=yes
```

3. `ssh` into the virtualbox centos instance 
