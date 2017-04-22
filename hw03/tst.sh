#!/bin/bash

for x in {1..6}
do
  echo encoding $x:
  bin/huffman -c -f test_cases/$x.in -o test_cases/$x.enc
  diff test_cases/$x.enc test_cases/$x.out
done
for x in {1..6}
do
  echo decoding $x:
  bin/huffman -u -f test_cases/$x.out -o test_cases/$x.dec
  diff test_cases/$x.dec test_cases/$x.in
done

rm test_cases/*.dec test_cases/*.enc