#!/bin/bash

/system reset-configuration

# Create bridges
/interface bridge add name=bridge30
/interface bridge add name=bridge31

# ether9 = Tux3 eth0
# ether13 = Tux4 eth0
# ether14 = Tux2 eth0
# ether16 = Tux4 eth1

# Remove default bridge ports
/interface bridge port remove [find interface = ether9]
/interface bridge port remove [find interface = ether13]
/interface bridge port remove [find interface = ether14]

# Add bridge ports
/interface bridge port add bridge = bidge30 interface = ether9 
/interface bridge port add bridge = bidge30 interface = ether13 
/interface bridge port add bridge = bidge31 interface = ether14

# Adding tux 4 eth1
/interface bridge port remove [find interface =ether16] 
/interface bridge port add bridge=bidge31 interface=ether16 