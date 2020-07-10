1. Update the system to the latest

``` bash
sudo apt upgrade 
```

2. Add header files

``` bash
sudo apt install raspberrypi-kernel-headers
```

3. Install Wireguard

``` bash 
# Add unstable repo which contains Wireguard
# Need to make sure it does not corrupt the stable environment 

echo "deb http://deb.debian.org/debian/ unstable main" | sudo tee --append /etc/apt/sources.list.d/unstable.list
wget -O - https://ftp-master.debian.org/keys/archive-key-$(lsb_release -sr).asc | sudo apt-key add -
sudo apt update
printf 'Package: *\nPin: release a=unstable\nPin-Priority: 150\n' | sudo tee --append /etc/apt/preferences.d/limit-unstable
sudo apt update


# Installation
sudo apt install wireguard
```


4. Configure Wireguard client

``` bash
# Generate client key at /etc/wireguard

wg genkey | sudo tee privatekey | wg pubkey | sudo tee publickey
```

```
# /etc/wireguard/wg0-client.conf
[Interface]
Address = 10.10.0.4/32
Address = fd86:ea04:1111::4/128
SaveConfig = true
PrivateKey = <your client private key here>
DNS = 8.8.8.8
PostUp = iptables -A FORWARD -i wlan0 -o wg0-client -j ACCEPT; iptables -A FORWARD -i wg0-client -o wlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT; iptables -t nat -A  POSTROUTING -o wg0-client -j MASQUERADE;
PostDown = iptables -D FORWARD -i wlan0 -o wg0-client -j ACCEPT; iptables -D FORWARD -i wg0-client -o wlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT; iptables -t nat -D  POSTROUTING -o wg0-client -j MASQUERADE;

[Peer]
PublicKey = <your server public key here>
Endpoint = <your server public ip>:51820
AllowedIPs = 0.0.0.0/0, ::/0
```

5. Configure route

``` bash
# If from Prepare-routed-wifi.md, use the following command to clean legacy configuration
sudo iptables -t nat -D POSTROUTING -o eth0 -j MASQUERADE
```

# Reference

1. [Installing and Configuring WireGuard on Raspberry Pi OS (May 2020)](https://www.sigmdel.ca/michel/ha/wireguard/wireguard_02_en.html)

2. [ xuyuji9000/wireguard-playground ](https://github.com/xuyuji9000/wireguard-playground/blob/master/Installation.md)

3. [Use Raspberry Pi as WiFi AP and route traffic through Wireguard (port 53)](https://blog.stigok.com/2019/03/26/raspberry-pi-wifi-ap-wireguard-port-53.html)
