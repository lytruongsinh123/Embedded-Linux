#!/bin/bash

read -p "Nhap xau can tim: " str
read -p "Nhap ten tap tin: " file

if [ ! -f "$file" ]; then
    echo "Tap tin khong ton tai"
    exit 1
fi

if grep -q "$str" "$file"; then
    echo "Tim thay xau '$str' trong tap tin"
else
    echo "Khong tim thay xau '$str'"
fi