This document give an example of using logrotate[1].

- What is logrotate for?

    `logrotate` is designed to ease administration of systems that generate large numbers of log files. It allows automatic rotation, compression, removal, and mailing of log files.

- cron configuration location: `/etc/cron.daily/logrotate`

- Force running:  ` logrotate --force CONFIG_FILE`



# Reference

1. [logrotate(8) - Linux man page](https://linux.die.net/man/8/logrotate)


2. [HowTo: The Ultimate Logrotate Command Tutorial with 10 Examples](https://www.thegeekstuff.com/2010/07/logrotate-examples/)

    > This article provides examples for reference.