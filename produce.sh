#!/bin/bash

#usage:  ./produce.sh new_data.txt | ./lottery.exe old_data.txt
awk '{print $2}' $1 | awk -F ',' '{print "a", $1, $2, $3, $4, $5}'
