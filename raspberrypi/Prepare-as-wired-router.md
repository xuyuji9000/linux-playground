1. Setup network bridge

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

2. Give IP to bridge device

```
#/etc/dhcpcd.conf
...
denyinterfaces wlan1 eth0
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
interface=wlan1
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

4. WiFi will work after reboot



# Reference

1. [Setting up a Raspberry Pi as a bridged wireless access point](https://www.raspberrypi.org/documentation/configuration/wireless/access-point-bridged.md)

2. [systemd-networkd](https://wiki.archlinux.org/index.php/Systemd-networkd)
