#!/bin/sh

sudo dnf group install "Development Tools" -y
sudo dnf install ncurses-devel -y
sudo dnf install elfutils-libelf-devel -y
sudo dnf install openssl-devel -y

# Repository PowerTools by default is not enabled
# use "dnf repolist --all" to check for more info.
sudo dnf config-manager --set-enabled powertools
sudo dnf install dwarves -y
