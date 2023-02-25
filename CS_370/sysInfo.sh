#!/bin/bash

# Lab: read bash script command line argument & show result based on command line argument
# if 1st argument == sys then show system information 
# if 1st argument == mem then show memory information
# if 1st argument == disk then show disk information
# if no argument then show error message
# if wrong argument then show error message

# if - else if - else for diff case 
if [ $# -ne 1 ]; then
    echo "Usage: sysInfo <sys|mem|disk>"
else
    # use bash guide and cheat sheet to use different comamands
    if [ $1 == "sys" ]; then
        echo -e "-------------------------------System Information----------------------------"
        echo -e "Hostname:\t\t"`hostname`
        echo -e "uptime:\t\t\t$(uptime | awk '{print $3,$4}' | sed 's/,//')" 
        echo -e "Manufacturer:\t\t"`cat /sys/class/dmi/id/chassis_vendor`
        echo -e "Product Name:\t\t"`cat /sys/class/dmi/id/product_name`
        echo -e "Version:\t\t"`cat /sys/class/dmi/id/product_version`
        echo -e "Machine Type:\t\t"`vserver=$(lscpu | grep Hypervisor | wc -l); if [ $vserver -gt 0 ]; then echo "VM"; else echo "Physical"; fi`
        echo -e "Operating System:\t"`hostnamectl | grep "Operating System" | cut -d ' ' -f3-5`
        echo -e "Kernel:\t\t\t"`uname -r`
        echo -e "Architecture:\t\t"`uname -m`
        echo -e "Processor Name:\t\t"`awk -F':' '/^model name/ {print $2}' /proc/cpuinfo | uniq | sed -e 's/^[ \t]*//'`
        echo -e "Active user:\t\t"`w -h | awk '{print $1}'` 
        echo -e "Main System IP:\t\t"`hostname -I`

    elif [ $1 == "mem" ]; then
        echo -e "-------------------------------CPU/Memory Usage------------------------------"
        free
        echo -e '\n'
        echo -e "Memory Usage:\t\t"`free | awk '/Mem/{printf("%.2f%%"), $3/$2*100}'`
        echo -e "Swap Usage:\t\t"`free | awk '/Swap/{printf("%.2f%%"), $3/$2*100}'`
        echo -e "CPU Usage:\t\t"`cat /proc/stat | awk '/cpu/{printf("%.2f%%\n"), ($2+$4)*100/($2+$4+$5)}' | awk '{print $0}' | head -1`
    
    elif [ $1 == "disk" ]; then
        echo -e "-------------------------------Disk Usage-------------------------------"
        echo -e `df -h | awk '$NF=="/"{printf "Disk Usage: %s\t\t\n\n", $5}'`
        echo -e '\n'
        df -Pha -t squashfs | sed s/%//g
    
    else
        echo -e "Error, invalid parameter."
    fi
fi
