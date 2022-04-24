#!/bin/bash

echo "" >> salida_Ej1DYV.dat
i=10000
a=2000000

while [ $i -lt $a ]
do
	./ejercicio1_DYV $i >> salida_Ej1DYV.dat
	let i+=79600
done

