#!/bin/bash
echo "" >> salida2b_mb.dat
i=100
a=10000
while [ $i -lt $a ] 
do
./mezclaBruta  $i >> salida2b_mb.dat
let i+=396
done
