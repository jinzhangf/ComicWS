#!/bin/bash

#usage:  ./produce.sh new_data.txt | ./lottery.exe old_data.txt
sed '1!G;h;$!d' $1 | awk '{print $2}' | awk -F ',' '{print "a", $1, $2, $3, $4, $5}'
