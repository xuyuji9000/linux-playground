This file is used to annotate `net_device` data structure.


# How to use this file?

- Reference for data structure field description during source coding reading 


# Annotation

``` C
struct net_device {
    // A unique ID, assigned to each device when it is registered with a call to dev_new_index
    int ifindex;
}
```
