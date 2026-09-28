#!/bin/bash

read -p "Nhap so a :" a
read -p "Nhap so b :" b
read -p "Nhap so c :" c

max=$a
if [ $b -gt $max ]; then 
    max=$b 
fi
if [ $c -gt $max ]; then 
    max=$c 
fi

echo "So max : $max"
exit 0
