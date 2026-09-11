#!/bin/bash

function is_prime() {
	n=$1
	if [ $n -lt 1 ]; then return 0
	fi
	for ((i=2;i<n;i++));do
		k=$(( $n % $i ))
		if [ $k -eq 0 ]; then return 0
		fi
	done
	return 1
}
read -p "Nhap n :" n
is_prime $n
if [ $? -eq 0 ]; then 
	echo "$n khong la so nguyen to"
else
	echo "$n la so nguyen to"
fi
exit 0
