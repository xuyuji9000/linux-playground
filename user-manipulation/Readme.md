This document provide user manipulation related examples.

useradd:

- Create user without home: `useradd --no-create-home USERNAME`

- Create user with home: `useradd --create-home USERNAME`

usermod:

- Change user home directory: `usermod --home /TARGET/DIRECTORY USERNAME`

- Disable user login: `usermod --shell /sbin/nologin USERNAME`


su: 

- switch to another user: `sudo su - ANOTHER_USER`


