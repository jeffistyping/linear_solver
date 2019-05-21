#!/usr/bin/env bash

make
goodtests=('test.txt' 'test2.txt' 'test3.txt' 'test4.txt' 'test5.txt')
badtests=('btest.txt' 'btest2.txt' 'btest3.txt')
printf "\n"
echo "[[ GOOD TESTS ]]"
for i in "${goodtests[@]}"; do
	echo "------------------"
	./solver ./tests/$i
	echo "Test: $i Complete"
done
printf "\n"
echo "[[ BAD TESTS ]]"
for i in "${badtests[@]}"; do
	echo "------------------"
	./solver ./tests/$i
	echo "Test: $i Complete"
done