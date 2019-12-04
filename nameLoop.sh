#!/bin/bash

#4 files in sample, edit the second number for the amount of files you have docked
for i in {1..4};
do
	str1="log"
	str2=".txt"
    #make sure to replace Sample_Ligands with your folder of ligands as needed
	cp Ligand_$i/log.txt Sample_Ligands/$str1$i$str2
done

