// File name: AutoDockOrganizer.cpp
// Author: Skanda Sastry
// Userid: sastrysk
// Email: skanda.k.sastry@vanderbilt.edu
// Description: Organizes log.txt files from AutoDock into one map, prints out a ranking of the compounds by best predicted binding affinity.
// Last Changed: 5/24/2018

#include <iostream>
#include <map>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

//map of ligand to affinity
typedef std::multimap<double, uint32_t> AffinityMap;


const uint32_t START_LIGAND = 1;

//The next line represents the total number of fragments in the library. 
//Here, 4 fragments were screened. If 1152 fragments were screened, one would change
//the next line to "1152."
const uint32_t END_LIGAND = 4;

//function header
const std::string processFile(const std::string& fname, uint32_t affinityContainingLine);
uint32_t atomCounter(const std::string& fname);

int main() {

    AffinityMap compoundMultiMap;
    
    std::string filePath;
    std::cout << "Enter the file path of the log files: " << std::endl;
    std::cin >> filePath;

    uint32_t bestPoseLine = 26;

    uint32_t whichMetric;
    
    std::cout << "Press 1 for raw affinity ranking, 2 for affinity/sqrt(non-H atoms)" << std::endl;
    std::cin >> whichMetric;
    while (whichMetric != 1 && whichMetric != 2) {
        std::cout << "Press 1 for raw affinity ranking, 2 for affinity/sqrt(non-H atoms)" << std::endl;
        std::cin >> whichMetric;
    } 

    //loops through each log file
    for (uint32_t i = START_LIGAND; i <= END_LIGAND; ++i) {

        //line with the affinity in it
        std::string affinityLine;
        std::string logTxtFile = (filePath + "/log" + std::to_string(i) + ".txt");
        affinityLine = processFile(logTxtFile, bestPoseLine);
        std::string rankStr;
        std::string affinityStr;

        std::stringstream lineStream(affinityLine);
        lineStream >> rankStr;
        lineStream >> affinityStr;


        std::string ligandPDBQTFile = (filePath + "/Ligand_" + std::to_string(i) + ".pdbqt");
        int atomCount = atomCounter(ligandPDBQTFile);
        //converts affinity value from string to double
        double affinity = std::stod(affinityStr, nullptr);
             
        // double efficiency = affinity/(atomCount);
        double efficiencySqrt = affinity/(sqrt(atomCount));
        // double efficiencyCubrt = affinity/(std::pow(atomCount,1./3.));


        //adds appropriate value to the map
        if (whichMetric == 1) {
            compoundMultiMap.insert(AffinityMap::value_type(affinity, i));
        } else if (whichMetric == 2) {
            compoundMultiMap.insert(AffinityMap::value_type(efficiencySqrt, i));
        }
        
    }
    
    uint32_t rank = 1;
    AffinityMap::const_iterator iter;
    std::ofstream myfile;
    myfile.open("results.txt");
    if (whichMetric == 1) {
        //new line
        myfile << "\n";
        myfile << "Printing Raw Affinity Values\n";
        myfile << "\n";

    } else if (whichMetric == 2) {
        myfile << "\n";
        myfile << "Printing Affinity Values Corrected for Ligand Size\n";
        myfile << "\n";
    }
    for (iter = compoundMultiMap.begin(); iter != compoundMultiMap.end(); ++iter) {
       	myfile << rank << "\t";
	    myfile << iter->first << "\t";
        myfile << "Ligand" << iter->second << "\n";
	++rank;
    }


}

//function reads the log file and returns the line w/ the highest affinity
const std::string processFile(const std::string& fname, uint32_t affinityContainingLine) {
    std::ifstream inFile(fname.c_str());
    std::string line;
    std::string affinityLine;
    uint32_t i = 1;

    if(!inFile) {
        std::cout << "Cannot open input file.";
        return "";
    }

    while (std::getline(inFile, line)) {
        if (i == affinityContainingLine) {
            affinityLine = line;
        }
        ++i;
    }

    return affinityLine;

}

//function reads the pdbqt file of the ligand and returns number of non-H and non-C atoms
uint32_t atomCounter(const std::string& fname) {
    int count = 0;
    std::string line;
    std::ifstream inFile(fname.c_str());

    //if program cannot open file
    if (!inFile) {
        std::cout << "Cannot open input pdbqt file.";
        return -1;
    }

    //tells whether the line represents an atom
    std::string firstWord;
    //meaningless second number
    std::string dummyNumber;
    //tells whether the atom is hydrogen or non-hydrogen
    std::string atomLetter;

    while (std::getline(inFile, line)) {
        std::stringstream lineStream(line);
        lineStream >> firstWord;
        if (firstWord == "ATOM") {
            lineStream >> dummyNumber;
            lineStream >> atomLetter;

            if (atomLetter != "H") {
                ++count;
            }
        }
    }

    return count;
}
