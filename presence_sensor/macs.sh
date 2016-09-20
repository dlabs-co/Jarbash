#!/bin/bash -l

macfile=$(cat maclist | cut -f 1)
users=$(cat maclist | cut -f 2)
USER=`whoami`

if [ $USER == "root" ]
	then
		echo # echo "el usuario es Root"
	else
		echo " Permission denied of this user: "$USER && exit
fi

if [ -z "$COUNT" ]; then
	export COUNT=0
fi

#Every 2 scans clear ARP table to reload it
if [ $COUNT =  2 ]
then
	$(sudo ip -s -s neigh flush all > /dev/null)
	export COUNT=0
fi

#Nmap to fill the ARP table for all devices in local net
$(sudo nmap -sn 192.168.1.1/24 > /dev/null)

mac_list=($macfile)
arps=$(arp -an | cut -f 4 -d ' ')

read -a arp_list <<< $arps
read -a user_list <<< $users

index=0

#Search for matches between mac lists
echo "Connected users:"

for x in ${mac_list[@]}
do
	for i in ${arp_list[@]}
	do
		if [ $i == $x ]
	       	then
			echo -e "\t\t ${user_list[$index]}"
		fi
	done
	((index++))
done

((COUNT++))
