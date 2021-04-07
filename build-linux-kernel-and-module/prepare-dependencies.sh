#!/bin/sh

dnf group install "Development Tools" -y
dnf install ncurses-devel -y
dnf install elfutils-libelf-devel -y
dnf install openssl-devel -y

# Repository PowerTools by default is not enabled
# use "dnf repolist --all" to check for more info.
dnf config-manager --set-enabled PowerTools
dnf install dwarves -y
