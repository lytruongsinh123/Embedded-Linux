#!/bin/bash

dem=1
while [ $dem -lt 6 ]; do
    echo "/----------------Menu------------------/"
	echo "[1] Show today date/time\n"
	echo "[2] Show all files in current directory\n"
	echo "[3] Show users\n"
	echo "[4] Show calendar\n"
	echo "[5] Exit/Stop\n"

	read -p "Nhap lua chon :" choice;
	if [ $choice -eq 1 ]; then
		echo "[1] Show today date/time\n"
		echo $(date)
	fi
	
	if [ $choice -eq 2 ]; then
		echo "[2] Show all files in current directory\n"
		echo $(ls)
	fi

	if [ $choice -eq 3 ]; then
		echo "[3] Show users\n"
		echo $(who)
	fi

	if [ $choice -eq 4 ]; then
		echo "[4] Show calendar\n"
		echo $(cal)
	fi

	if [ $choice -eq 5 ]; then
		break
	fi
    dem=$(($dem + 1))
done
exit 0
