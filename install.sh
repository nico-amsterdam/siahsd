#!/usr/bin/env bash
sudo apt-get install libdbi-dev libtalloc-dev nettle-dev
sudo apt-get install libtevent-dev
sudo apt-get install build-essential libgtk2.0-dev libperl-dev libtalloc-dev libtevent-dev samba-dev mariadb-server mariadb-client libgmp-dev nettle-dev
sudo mkdir /var/log/siahsd
sudo chmod 777 /var/log/siahsd
sudo cp siahsd.conf /etc
samba -V
# On my system, output is: Version 4.3.11-Ubuntu
make
# if make is succesfull, the executables will be in the build directory
