#! /bin/bash

for f in Sample_Ligands/Ligand_*.pdbqt; #iterates through a folder with ligand files
do
    b=`basename $f .pdbqt` 
    echo Processing ligand $b
    mkdir -p $b
    #vina command for a config file "config.txt", outputs an out file with docking scores and a log file
    /programs/x86_64-linux/vina/1.1.2/bin/vina --config config.txt --ligand $f --out ${b}/out.pdbqt --log ${b}/log.txt 
done
