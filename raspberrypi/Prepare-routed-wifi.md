1. Prepare DHCP server and DNS service 

``` bash
# Install **dnsmasq** for DNS, DHCP services
sudo apt install dnsmasq
```

``` bash
# Backup original config
sudo mv /etc/dnsmasq.conf /etc/dnsmasq.conf.orig
```

```
# Configure dnsmasq
# /etc/dnsmasq.conf
interface=wlan0
dncp-range=192.168.4.2,192.168.4.20,255.255.255.0,24h
domain=wlan
address=/gw.wlan/192.168.4.1                            # Alias for the router
```

2. Set Router ip through DHCP  

```
# /etc/dhcpcd.conf
interface wlan0
    static ip_address=192.168.4.1/24
    nohook wpa_supplicant
```

3. Configure access point 

```
# Install **hostapd** for WIFI authentication 
sudo apt install hostapd
```

```
# /etc/hostapd/hostapd.conf
country_code=CN
interface=wlan0
ssid=06402
hw_mode=g
channel=7
macaddr_acl=0
auth_algs=1
ignore_broadcast_ssid=0
wpa=2
wpa_passphrase=AardvarkBadgerHedgehog
wpa_key_mgmt=WPA-PSK
wpa_pairwise=TKIP
rsn_pairwise=CCMP
```

4.1. Enable ip forwarding

```
# /etc/sysctl.conf
# Enable IP forwarding as persistent state 
net.ipv4.ip_forward = 1
```

```
# Enable IP forwarding for running system
sudo sysctl -w net.ipv4.ip_forward=1
```

4.2. Prepare route

```
sudo apt install netfilter-persistent iptables-persistent
```

```
sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
sudo netfilter-persistent save
```


# Reference

1. [Setting up a Raspberry Pi as a routed wireless access point](https://www.raspberrypi.org/documentation/configuration/wireless/access-point-routed.md)

2. [How to Disable/Enable IP forwarding in Linux](https://linuxconfig.org/how-to-turn-on-off-ip-forwarding-in-linux)
