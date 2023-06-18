Use Raspberry Pi, ShadowsocksR Plus to setup the home network VPN.

1. Setup the Openwrt on Raspberry Pi  

    Download Raspberry Pi image from [固件下载](https://doc.openwrt.cc/2-OpenWrt-Rpi/1-Download/) .
   
2. Setup guest wifi

    Guest wifi's firewall needs to accept forward.<br>
    And the **LAN** interface needs to accept masquerading. <br>
    **GUEST** interface needs to set custom DNS.  

3. Prepare ShadowsocksR Plus+  

    Add subscription URL from [少数派](https://sspcloud.net/) <br>
    Point the interface to **GUEST** interface.
