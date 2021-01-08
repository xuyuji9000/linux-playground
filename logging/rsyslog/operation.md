This document is used to support **rsyslog** operations.

# Steps

- Install rsyslog on CentOS

  - Default log location: `/var/log/messages`

  - Create a simple log: `echo "simple log"| logger `

  - Check if configuration correct: `rsyslogd -f /etc/rsyslog.conf -N1`

- Filter log [3][4]

    - Syntax
      
      ```
      :[Available Properties], [compare-operations], [customized expression] [path/log file]
      ```
    
    - Example

      ```
      :programname, isequal, "application-1" /var/log/application-1.log
      ```

      > programname is the “static” part of the tag[4]

      > Check if configuration is correct `rsyslogd -f /etc/rsyslog.conf -N1`

    - Prepare testing message

      ``` bash
      # Create a message with tag
      echo "hell world" | logger -i --tag application-1
      ```

- rotate log

- Present log with a UI


# Architecture


![logging architecture](./logging-architecture.png)


> A simple logging design with **rsyslog**


# Reference

1. [How to Configure Rsyslog Server in CentOS 8 / RHEL 8](https://www.linuxtechi.com/configure-rsyslog-server-centos-8-rhel-8/)


2. [how to filter rsyslog messages by tags](https://serverfault.com/questions/514901/how-to-filter-rsyslog-messages-by-tags)

3. [Filter Conditions](https://www.rsyslog.com/doc/master/configuration/filters.html)

4. [rsyslog Properties](https://www.rsyslog.com/doc/master/configuration/properties.html)

