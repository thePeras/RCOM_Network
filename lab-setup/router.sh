#!/bin/bash

/system reset-configuration

# eth1 = Lab Net
# eth2 = Switch

/ip address add address=172.16.2.39/24 interface=ether1
/ip address add address=172.16.31.254/24 interface=ether2

/ip route add dst-address=172.16.30.0/24 gateway=172.16.31.253
#/ip route add dst-address=0.0.0.0/0 gateway=172.16.2.254
/ip route print