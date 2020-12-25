#!/usr/bin/env bash
sudo apt-get install -y libdbi-dev libtalloc-dev nettle-dev
sudo apt-get install -y libtevent-dev
sudo apt-get install -y build-essential libgtk2.0-dev libperl-dev libtalloc-dev libtevent-dev samba-dev mariadb-server mariadb-client libgmp-dev nettle-dev
sudo apt-get install -y python2 
# This can conflict with python-is-python3 on your system:
sudo apt-get install -y python-is-python2
sudo mkdir /var/log/siahsd
sudo chmod 777 /var/log/siahsd
sudo cp siahsd.conf /etc
bin/waf configure
samba -V
# On my systems, output is: Version 4.3.11-Ubuntu or 4.11.6-Ubuntu
make
# if make is succesfull, the executables will be in the build directory
# For IRIS touch / chiron use bin/chirond
