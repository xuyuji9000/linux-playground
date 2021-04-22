This file documents learning about `header_ops` field of `struct net_device`.

- Description from `struct net_device`

``` C
// include/linux/netdevice.h

// @header_ops:	Includes callbacks for creating,parsing,caching,etc
// 			of Layer 2 headers.
```

- Definiation

``` C
// include/linux/netdevice.h

// Here header_ops looks like a interface
// Each net_device data strcuture instance can implement the function pointers listed
struct header_ops {
	int	(*create) (struct sk_buff *skb, struct net_device *dev,
			   unsigned short type, const void *daddr,
			   const void *saddr, unsigned int len);
	int	(*parse)(const struct sk_buff *skb, unsigned char *haddr);
	int	(*cache)(const struct neighbour *neigh, struct hh_cache *hh, __be16 type);
	void	(*cache_update)(struct hh_cache *hh,
				const struct net_device *dev,
				const unsigned char *haddr);
	bool	(*validate)(const char *ll_header, unsigned int len);
	__be16	(*parse_protocol)(const struct sk_buff *skb);
};

```

- How is `header_ops` used?

``` C
// include/linux/netdevice.h

static inline int dev_hard_header(struct sk_buff *skb, struct net_device *dev,
				  unsigned short type,
				  const void *daddr, const void *saddr,
				  unsigned int len)
{
	if (!dev->header_ops || !dev->header_ops->create)
		return 0;

	return dev->header_ops->create(skb, dev, type, daddr, saddr, len);
}
```

- Where is `dev_hard_header` used?

``` C
// It is consumed inside 
// net/packet/af_packet.c


// along with 
// - dev_parse_header
// - dev_parse_header_protocol
// - dev_validate_header
// - dev_has_header
```





































