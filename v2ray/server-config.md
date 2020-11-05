- Prepare a machine at Google Cloud Taiwan Region

    Machine Size: f1-micro

    OS: Ubuntu 20.04 LTS

- Download V2ray from here[2]

- Installation commands[3]

  ``` bash
  wget https://raw.githubusercontent.com/v2fly/fhs-install-v2ray/master/install-release.sh
  sudo bash ./install-release.sh

  # Related files
  #installed: /usr/local/bin/v2ray
  #installed: /usr/local/bin/v2ctl
  #installed: /usr/local/share/v2ray/geoip.dat
  #installed: /usr/local/share/v2ray/geosite.dat
  #installed: /usr/local/etc/v2ray/config.json
  #installed: /var/log/v2ray/
  #installed: /var/log/v2ray/access.log
  #installed: /var/log/v2ray/error.log
  #installed: /etc/systemd/system/v2ray.service
  #installed: /etc/systemd/system/v2ray@.service
  ```


- Configuration examples[4]

  Get configuration file scaffold and configure parameters.
  
  > Generate uuid: `v2ctl uuid`

- Prepare TLS certificate

  ``` bash
  acme.sh --install-cert -d DOMAINNAME  \
  --ecc \
  --key-file /usr/local/etc/v2ray/v2ray.key \
  --fullchain-file /usr/local/etc/v2ray/v2ray.crt \
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

2. [v2fly/v2ray-core releases](https://github.com/v2fly/v2ray-core/releases)


3. [v2fly/fhs-install-v2ray](https://github.com/v2fly/fhs-install-v2ray)


4. [v2fly/v2ray-examples](https://github.com/v2fly/v2ray-examples)
