#!/bin/bash

systemctl restart networking

ifconfig eth0 up
ifconfig eth0 172.16.30.1/24

read -n 1 -p "Configured for exp2, want more? Press any key when ready..."

route add -net 172.16.31.0/24 gw 172.16.30.254

read -n 1 -p "Configured for exp3, want more? Press any key when ready..."

route add default gw 172.16.30.254

read -n 1 -p "Configured for exp4, want more? Press any key when ready..."

# configure DNS
echo 'nameserver 193.136.28.10' > /etc/resolv.conf