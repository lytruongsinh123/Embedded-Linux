#!/bin/bash

read -p "Nhap ten tap tin: " file

if [ ! -f "$file" ]; then
    echo "Tap tin khong ton tai"
    exit 1
fi

count=$(wc -l < "$file")

echo "So dong cua tap tin: $count"