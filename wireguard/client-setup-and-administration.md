This document contains setup and administration instructions for Wireguard client.

# Setup

1. Install Wireguard client. 

``` bash
# Assuming platform as Macos
brew install -dv wireguard-tools
```



2. Generate client key

    ``` bash
    # Configuration path
    cd /usr/local/etc/wireguard/
    
    umask 077
    wg genkey | sudo tee privatekey | wg pubkey | sudo tee publickey
    ```

9. Add configuration to client

``` bash
[Interface]
Address = 10.10.0.2/32
Address = fd86:ea04:1111::2/128
SaveConfig = true
PrivateKey = <your client private key here>
DNS = 1.1.1.1

[Peer]
PublicKey = <your server public key here>
Endpoint = <your server public ip>:51820
AllowedIPs = 0.0.0.0/0, ::/0
```

10. Add client public key to server

    ``` bash
    wg set wg0 peer <client-public-key> allowed-ips 10.10.0.2/32,fd86:ea04:1111::2/128
    ```

11. Enable client connection.

``` bash
wg-quick up wg0
```


# Administration

- Get interface configuration

``` bash
# Find it here on macos
ls /usr/local/etc/wireguard/INTERFACE_NAME.conf
```

- INTERFACE_NAME is also needed for `wg-quick`
