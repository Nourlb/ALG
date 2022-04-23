#!/bin/bash

echo "" >> salida_Ej2a_MB.dat
i=100
a=10000

while [ $i -lt $a ]
do
	./mezclaBruta $i >> salida_Ej2a_MB.dat
	let i+=396
done
