#!/bin/bash

read -p "Nhap duong dan tap tin: " file

if [ -e "$file" ]; then
    echo "Tap tin ton tai"
else
    echo "Tap tin khong ton tai"
fi