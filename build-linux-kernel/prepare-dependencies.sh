#!/bin/sh

dnf group install "Development Tools"
dnf install ncurses-devel
dnf install elfutils-libelf-devel
dnf install openssl-devel

# Repository PowerTools by default is not enabled
# use `dnf repolist --all` to check for more info.
dnf config-manager --set-enabled PowerTools
dnf install dwarves
