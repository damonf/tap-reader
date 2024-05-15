
Run it:
`sudo ./tap tap0`
Give the device an IP address
`sudo ip addr add 192.168.100.9/24 dev tap0`
Bring the device up
`sudo ip link set up dev tap0`
