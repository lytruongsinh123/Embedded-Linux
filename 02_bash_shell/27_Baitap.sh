#!/bin/bash

function sum_2_number() {
	echo $(($1 + $2))
}
read -p "Nhap so phan tu n: " n
echo "Nhap cac phan tu"
for ((i=0; i<n; i++)); do
	read -p "a[$i] = " a[$i]
done

sum=0

echo "Cac phan tu chan"
for((i=0; i < n; i++)); do
	if [ $((${a[$i]} % 2)) -eq 0 ]; then
		echo -n "${a[$i]} "
		sum=$(sum_2_number $sum ${a[$i]})
	fi
done
echo
echo "Tong cac phan tu chan : $sum"
exit 0
