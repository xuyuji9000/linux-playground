1. Setup network bridge

> This can also implemented by **ip** command, but it is gone after reboot

```
# add a bridge network 
# /etc/systemd/network/bridge-br0.netdev
[NetDev]
Name=br0
Kind=bridge
```

```
# add built-in Ethernet interface as a bridge member 
# /etc/systemd/network/br0-member-eth0.network
[Match]
Name=eth0

[Network]
Bridge=br0
```

``` bash
sudo systemctl restart systemd-networkd
sudo systemctl enable systemd-networkd
```

2. Give IP to bridge device

```
#/etc/dhcpcd.conf
...
denyinterfaces wlan0 eth0
interface br0
...
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
bridge=br0
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

```
# /etc/default/hostapd
...
DAEMON_CONF="/etc/hostapd/hostapd.conf"
...
```

``` bash
sudo systemctl restart hostapd
sudo systemctl enable hostapd
```

4. WiFi will work after reboot


# Problems

- With this setup, laptop connecting into the 'router' is able to connect Internet, but the router is not able to access Internet now.


# Reference

1. [Setting up a Raspberry Pi as a bridged wireless access point](https://www.raspberrypi.org/documentation/configuration/wireless/access-point-bridged.md)

2. [systemd-networkd](https://wiki.archlinux.org/index.php/Systemd-networkd)

3. [Network bridge](https://wiki.archlinux.org/index.php/Network_bridge)
