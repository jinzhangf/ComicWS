#!/bin/bash

#set -x
#usage: ./cat.sh data/2018/

if [ ! -d $1 ];then
	echo "Error. Usage: ./cat.sh dir"
	exit 1
fi

files=`find $1 -name "*.txt"`
for file in $files; do
{
	sed -e '/=/d;/号码/d' ${file} > ${file}.tmp
	sed -e '1!G;h;$!d' ${file}.tmp > ${file}.tmp.tmp
	mv ${file}.tmp.tmp ${file}.tmp
}
done

tmp_files=`find $1 -name "*.tmp" | sort`
cat $tmp_files > cat.out.txt
rm $tmp_files
