#!/bin/bash

readarray -t arr < file.txt
echo ${arr[@]}
exit 0
