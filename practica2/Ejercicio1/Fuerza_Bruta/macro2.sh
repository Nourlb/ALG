#!/bin/bash

echo "" >> salida_Ej1Obvio2.dat
i=100
a=200000

while [ $i -lt $a ]
do
	./Ejercicio1_Obvio $i >> salida_Ej1Obvio2.dat
	let i+=7996
done

