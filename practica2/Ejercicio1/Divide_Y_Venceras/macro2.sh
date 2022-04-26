#!/bin/bash

echo "" >> salida_Ej1DYV.dat
i=100
a=200000

while [ $i -lt $a ]
do
	./ejercicio1_DYV $i >> salida_Ej1DYV.dat
	let i+=7996
done

