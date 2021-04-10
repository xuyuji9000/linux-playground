# Introduction

This article aims to incorporate Wireguard VPN setup process into my own knowledge structure.

# Spec

- Linux Version: Ubuntu 19.10
  > Wireguard join Linux Kernel on 5.6, so need a up-to-date kernel

- Server from Google Cloud Taiwan
  > Seems Google Cloud Server has pretty good access performance from mainland

# STEPS

1. Install wireguard on Ubuntu 19.10


    ``` bash
    sudo add-apt-repository ppa:wireguard/wireguard
    sudo apt-get update
    sudo apt-get install wireguard
    ```

2. Check if wireguard is module

    ``` bash
    sudo modprobe wireguard
    sudo lsmod | grep wireguard
    ```

3. Generate key

    ``` bash
    cd /etc/wireguard
    umask 077
    wg genkey | sudo tee privatekey | wg pubkey | sudo tee publickey
    ```
4. Add wireguard configuration to **/etc/wireguard/wg0.conf**

``` 
[Interface]
PrivateKey = <your_server_private_key_here>
Address = 10.10.0.1/24
Address = fd86:ea04:1111::1/64
SaveConfig = true
PostUp = iptables -A FORWARD -i wg0 -j ACCEPT; iptables -t nat -A POSTROUTING -o <your_main_network_interface_name> -j MASQUERADE; ip6tables -A FORWARD -i wg0 -j ACCEPT; ip6tables -t nat -A POSTROUTING -o <your_main_network_interface_name> -j MASQUERADE
PostDown = iptables -D FORWARD -i wg0 -j ACCEPT; iptables -t nat -D POSTROUTING -o <your_main_network_interface_name> -j MASQUERADE; ip6tables -D FORWARD -i wg0 -j ACCEPT; ip6tables -t nat -D POSTROUTING -o <your_main_network_interface_name> -j MASQUERADE
ListenPort = 51820
```

    > You can look into the network interfaces with `ifconfig` || `ip -c a` command


5. Enable ip forward on Linux kernel

``` bash
cat << EOF >> /etc/sysctl.conf
net.ipv4.ip_forward=1
net.ipv6.conf.all.forwarding=1
EOF
sysctl -p
```

6. Enable wg0

    ``` bash
    wg-quick up wg0
    ```

7. Install Wireguard client. I'm use [MacOS](https://www.wireguard.com/install/)

8. Generate client key

    ``` bash
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

# Reference

1. [vpn-server-using-wireguard-on-ubuntu](https://securityespresso.org/tutorials/2019/03/22/vpn-server-using-wireguard-on-ubuntu/)
