Dissect wireguard source code as a linux kernel module

``` C
// linux/drivers/net/wireguard/device.c
int __init wg_device_init(void) 
{
    // ...
    ret = register_pernet_device(&pernet_ops);
    // ...
}

```

``` C
// linux/net/core/net_namespace.c
int register_pernet_device(struct pernet_operations *ops)
{
    // ...
    error = register_pernet_operations(&pernet_list, ops);
    // ...
}

static int register_pernet_operations(struct list_head *list,
				      struct pernet_operations *ops)
{
    // ...
    error = __register_pernet_operations(list, ops);
    // ...
}

static int __register_pernet_operations(struct list_head *list,
					struct pernet_operations *ops)
{
    // ...
    list_add_tail(&ops->list, list);
    // ...
}
```

``` C
// linux/include/linux/list.h
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}


static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
    
}
```