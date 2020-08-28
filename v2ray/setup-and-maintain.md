
# Operation commands

- generate domain name: 

``` bash
acme.sh --install-cert -d DOMAINNAME  \
--ecc \
--key-file /etc/v2ray/v2ray.key \
--fullchain-file /etc/v2ray/v2ray.crt \
--reloadcmd     "service nginx force-reload"
```

- renew certificate: 

``` bash
acme.sh --renew \
-d DOMAINNAME \
--ecc
```


# Reference 

1. [ WebSocket + TLS + Web](https://guide.v2fly.org/advanced/wss_and_web.html)