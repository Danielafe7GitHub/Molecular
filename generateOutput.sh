#!/bin/bash

#mkdir inputs

val=832
for i in 50 100 150 200
do
	for j in 0 1 2
	do	
	    newval=$(($val - i))
	    echo "832 ${newval} ${j}" > "inputs/${i}${j}.in"
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
    echo "832 ${i} 0" > "inputs/${i}xx.in"
    cat plantilla.txt >> "inputs/${i}xx.in"
    ./disociativo.o < "inputs/${i}xx.in" > "outputs/disociativo${i}.txt"
done
