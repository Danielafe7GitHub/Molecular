#!/bin/bash

#mkdir inputs

for i in 50 100 150 200
do
	for j in 0 1 2
	do	
		echo "832 ${i} ${j}" > "inputs/${i}${j}.in"
		cat plantilla.txt >> "inputs/${i}${j}.in"
		if [ $j -eq 0 ]
		then
			./amalgamiento.o < "inputs/${i}${j}.in" > "outputs/amalgamientosimple${i}.txt"
		fi
		if [ $j -eq 1 ]
		then
			./amalgamiento.o < "inputs/${i}${j}.in" > "outputs/amalgamientocompleto${i}.txt"
		fi
		
		if [ $j -eq 2 ]
		then
			./amalgamiento.o < "inputs/${i}${j}.in" > "outputs/amalgamientopromedio${i}.txt"
		fi
	done
done

for i in 50 100 150 200
do
	./disociativo.o < "inputs/${i}0.in" > "outputs/disociativo${i}.txt"
done
