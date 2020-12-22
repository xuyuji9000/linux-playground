#!/bin/sh

df -HP | grep -vE '^Filesystem|tmpfs|cdrom' | awk '{ print $5 " " $1 }' | while read output;
do 
    usage_percentage=$(echo ${output} | awk '{ print $1}' | cut -d'%' -f1)
    partition=$(echo ${output} | awk '{ print $2}')
    if [ ${usage_percentage} -ge 90 ]; then
        echo "Running out of space \"${partition} (${usage_percentage}%)\""
        mail -s "Alert: Almost out of disk space $usep%" you@somewhere.com
    fi
done 
