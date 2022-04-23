#!/bin/bash

echo "" >> salida_Ej2b_DYV.dat
i=100
a=10000

while [ $i -lt $a ]
do
	./mezclaDYV $i >> salida_Ej2b_DYV.dat
	let i+=396
done
