#!/bin/bash

/system reset-configuration

# Create bridges
/interface bridge add name=bridge30
/interface bridge add name=bridge31

# ether9 = GNU3 eth0
# ether13 = GNU4 eth0
# ether14 = GNU2 eth0
# ether16 = GNU4 eth1

# Remove default bridge ports
/interface bridge port remove [find interface = ether9]
/interface bridge port remove [find interface = ether13]
/interface bridge port remove [find interface = ether14]

# Add bridge ports
/interface bridge port add bridge = bidge30 interface = ether9 
/interface bridge port add bridge = bidge30 interface = ether13 
/interface bridge port add bridge = bidge31 interface = ether14

# Adding GNU4 eth1
/interface bridge port remove [find interface =ether16] 
/interface bridge port add bridge=bidge31 interface=ether16 