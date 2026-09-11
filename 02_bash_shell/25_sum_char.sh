#!/bin/bash

read -p "Nhap so : " num

sum=0
while [ $num -gt 0 ]; do
	sum=$(($sum + num % 10))
	num=$(($num / 10))
done
echo "Tong cac chu so : $sum"
exit 0
