#!/bin/bash

#read the process name from the command line 
process=$1
#and include some error checking (i.e., for non-existent processes).  
if [ -z "$process" ]; then
    echo "Usage: $0 process_name"
    exit 1
fi
#If the process exists, then grab the process ID and print it out.
# by using the pidof command 

pid=$(pidof -s $process)
if [ -z "$pid" ]; then
    echo "Process $process not found"
    exit 1
fi
echo "Process $pid Information"

#output voluntary_ctxt_switches: into terminal
echo "$(cat /proc/$pid/status | grep voluntary_ctxt_switches)"
#output nonvoluntary_ctxt_switches:
#echo "nonvoluntary_ctxt_switches: $(cat /proc/$pid/status | grep nonvoluntary_ctxt_switches | awk '{print $2}')"

#output user time and system time
USRTIME=`echo "scale=2; $(cat /proc/$pid/stat | cut -d' ' -f14) / $(getconf CLK_TCK)" | bc`
SYSTIME=`echo "scale=2; $(cat /proc/$pid/stat | cut -d' ' -f15) / $(getconf CLK_TCK)" | bc`
echo "User Time: $USRTIME"
echo "System Time: $SYSTIME"
# The total time is the user time and the system time added.  Since these are real values, awk can be used to add them
echo "Total Time: $(echo "$USRTIME + $SYSTIME" | bc)"
#The start time can be obtained using the ps command with the PID using the -o start option. 
# The output will contain headers which can be eliminated in multiple ways (one of which is grep).
echo "Start Time: $(ps -p $pid -o start | tail -1)" 




