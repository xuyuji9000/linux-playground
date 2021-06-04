This file contains learning about *weechat*.


- Scroll up: `fn + Up`


- Add new server

``` weechat
/server add libera irc.ea.libera.chat/6697 -ssl -autoconnect
```

- Join a channel 

``` weechat
/join #wireguard
```

- Generate password

``` shell 
openssl rand -base64 10
```

- Register nickname

``` weechat
/nick YourNick

/msg NickServ REGISTER YourPassword youremail@example.com
```

- Login 

``` weechat
/msg NickServ IDENTIFY <username> <password>
```


