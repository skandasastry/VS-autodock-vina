# Virtual Screening with AutoDock Vina

Skanda Sastry

This repository contains a set of scripts that aids Virtual Screening by Molecular Docking using AutoDock Vina, a docking software developed at the Scripps Institute. I have provided a script that allows a user to dock a set of ligands against a target receptor, then sort them on the basis of ligand affinity according to Vina's scoring function as well as another scoring metric to account for ligand atomic weight, since scoring functions are typically biased toward higher-MW compounds.


To do VS with Vina using this repository, follow these steps:
1. Download AutoDock Vina and the rest of the suite (AutoDock Tools GUI, etc.) from this link: http://vina.scripps.edu/download.html

2. Generate a set of separate ligand PDBQT files. In order to perform virtual screening successfully with AutoDock Vina, each ligand must be contained in its own PDBQT file. If you have ligands in another file format, OpenBabel can be used to convert them. Sample ligands are provided in the Sample_Ligands/ folder.

3. Prepare the receptor file for docking by removing waters, ions, cofactors, etc. just as for single docking. 
The examples given in this folder (apoReceptorMonomer.pdb) and (receptorMonomerAligned.pdb) have been fully prepared. 

4. Open the receptor file in AutoDock Tools, and find the area whose surface you would like to search for binding pockets. The sample file receptorMonomerAligned.pdb is a crystal structure with a fragment bound at a site in order to guide placement of the grid box around the general vicinity of this fragment. Understand that docking is quite finnicky and almost never works if an algorithm has to search the entire surface of the protein so it is much more optimal to concentrate on a small region. 

5. Generate a Vina configuration file in AutoDock Tools that specifies the information of the grid. A sample config file is given, but make sure the grid is placed in the exact coordinates where you want it! This is done in the exact same way as single docking, and the tutorials for this can be found in the following links: 
https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4868550/
http://vina.scripps.edu/tutorial.html
http://vina.scripps.edu/manual.html

6. After adjusting the grid and generating a Vina configuration file in AutoDock Tools (same as single docking), edit and execute vina_screen_local.sh. Currently, the file is written to iterate through a directory containing ligands titled Ligand_1.pdbqt, Ligand_2.pdbqt, and so on. The program will output an “out” PDBQT file with the highest scoring poses and a “log” txt file with the docking scores, in a separate directory for each ligand.

7.  Once Vina has docked all the ligands in the folder, extract the log files from each directory using nameLoop.sh - make sure to specify how many files are being docked in the nameLoop.sh Script! This will bring the log files out of their separate directories, so AutoDockOrganizer can extract their scores and sort them. Ensure that the log files are in the same folder as the ligand files themselves (the nameLoop script should have taken care of this). AutoDockOrganizer will read the original ligand files in order to calculate ligand efficiency if needed. A sample folder containing the original ligand files and log files containing the docking scores is given in Sample_Results.


8. Compile AutoDockOrganizer with the following command (without quotes)
"g++ -std=c++11 AutoDockOrganizer.cpp -o AutoDockOrganizer"

9. For folder path, enter the name of the folder containing the log files and the original Ligand PDBQT files. Select whether you would like a raw docking score ranking or a ranking by ligand efficiency.

10. View the results in results.txt. (Sample results.txt file is given based on the 4 sample ligands). However, remember that Vina's algorithm begins with a random seed and thus docking scores are not perfectly reproducible.



Many thanks to Dr. Oleg Trott and Scripps Institute for developing Vina: 
O. Trott, A. J. Olson, AutoDock Vina: improving the speed and accuracy of docking with a new scoring function, efficient optimization and multithreading, Journal of Computational Chemistry 31 (2010) 455-461

The protein structure used is that of the Receptor of Advanced Glycation Endproducts, from the PDB:
https://www.rcsb.org/structure/3CJJ

Thank you to Walter Chazin and Natasha Kozlyuk who guided and mentored me on this project.

All other scripts and files in this repository are my own work.
