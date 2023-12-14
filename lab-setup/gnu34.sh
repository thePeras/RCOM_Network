#!/bin/bash

systemctl restart networking

ifconfig eth0 up
ifconfig eth0 172.16.30.254/24

read -n 1 -p "Configured for exp2, want more? Press any key when ready..."

ifconfig eth1 up
ifconfig eth1 172.16.31.253/24

# enable IP forwarding
sysctl net.ipv4.ip_forward=1

# disable ICMP echo-ignore-broadcast
sysctl net.ipv4.icmp_echo_ignore_broadcasts=0

read -n 1 -p "Configured for exp3, want more? Press any key when ready..."

route add default gw 172.16.31.254

read -n 1 -p "Configured for exp4, want more? Press any key when ready..."

echo 'nameserver 193.136.28.10' > /etc/resolv.conf
