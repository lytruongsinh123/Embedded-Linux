#!/bin/bash

function hello() {
	echo "Hello $2"
}
hello Do Tuan Hung
x="A"
y="B"
function Test_Bien() {
	local x="C"
	y="B"
}
Test_Bien
echo "x : $x    y : $y"
function Test_Return(){
	return 15
}
echo $(Test_Return)

x=0
function Test_Return1() {
	x=10
}
Test_Return1
echo $x

x=0
function Test_Return2() {
	local name=$(($1 + $2))
	echo "$name"
}
Return_Value="$(Test_Return2 1 2)"
echo "ket qua la $Return_Value"
