- Install rsyslog on CentOS

  - Default log location: `/var/log/messages`

  - Create a simple log: `echo "simple log"| logger `

  - Check if configuration correct: `rsyslogd -f /etc/rsyslog.conf -N1`

- Pipe typed log to specific file

- rotate log

- Present log with a UI


# Reference

1. [How to Configure Rsyslog Server in CentOS 8 / RHEL 8](https://www.linuxtechi.com/configure-rsyslog-server-centos-8-rhel-8/)


2. [how to filter rsyslog messages by tags](https://serverfault.com/questions/514901/how-to-filter-rsyslog-messages-by-tags)