#!/bin/bash

arr=(1 2 3 4 5)
echo $arr
echo ${arr[2]}
echo ${arr[@]}
echo ${arr[@]:1}
echo ${arr[@]:1:2}
arr+=(6)
echo ${arr[@]}
unset arr[3]
echo ${arr[@]}
exit 0
