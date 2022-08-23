#!/usr/bin/env sh

count=0

while [ true ]; do
	sh $1
	if [ $? -ne 0 ]; then
		echo "count: $count"
		exit 1
	fi
	let count=count+1
done
