#!/bin/bash

clear
read -p "Nhap tan thu muc : " namefolder
mkdir $namefolder
if [ $? -eq 0 ]; then 
	clear
	echo "Thu muc $namefolder da duoc tao"
else
	clear
	echo "Ko the tao $namefolder"
fi
exit 0
