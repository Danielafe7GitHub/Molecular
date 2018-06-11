#!/bin/bash


for i in 3 5 10 
do
	for j in 50 100 1000 3500
	do
		echo "$i $j" > auxin.gg
		./generateMSA.o < auxin.gg > "inputsFinal/prueba$i$j.in"
		./Final.o < "inputsFinal/prueba$i$j.in" > "outputsFinal/${i}Seqs${j}Length-PaperOutput.out"
		./msa.o < "inputsFinal/prueba$i$j.in" > "outputsFinal/${i}Seqs${j}Length-NaiveOutput.out"
	done
done


for i in 10 100 1000
do
	for j in  5 10 100
	do
		echo "$i $j" > auxin.gg
		./generateMSA.o < auxin.gg > "inputsFinal/prueba$i$j.in"
		./Final.o < "inputsFinal/prueba$i$j.in" > "outputsFinal/${i}Seqs${j}Length-PaperOutput.out"
		./msa.o < "inputsFinal/prueba$i$j.in" > "outputsFinal/${i}Seqs${j}Length-NaiveOutput.out"
	done
done
