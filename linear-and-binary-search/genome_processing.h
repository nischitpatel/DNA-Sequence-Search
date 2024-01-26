/*
    Author: Nischit Bipinbhai Patel
    NAU ID #: 6293990
    Course: INF503 Large scale data structures
*/

#ifndef GENOMEPROCESSING_H
#define GENOMEPROCESSING_H

// Pre-processors
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;

#define HEADER '>'

class GENOMEPROCESSING
{
private:
    // Variable to store size of genome
    long long int genome_size = 0;

    // Array to store genome data
    char *genome_data;

public:
    /*
        Function name: getGenomeSize()
        Input parameter: NONE
        Output parameter (return): genome_size
    */
    long long int getGenomeSize();

    /*
        Function name: getGenomeData()
        Input parameter: NONE
        Output parameter: *genome_data - pointer to genome data array
    */
    char *getGenomeData();

    /*
        Function name: setGenomeSize()
        Input parameter: size - size of genome
        Output parameter: NONE
    */
    void setGenomeSize(long long int size);

    /*
        Function name: calculateGenomeSize()
        Input parameter: input_file_pointer - pointer to an input file
        Output parameter (return): total genome characters in a file 
    */
    long long int calculateGenomeSize(ifstream &input_file_pointer);

    /*
        Function name: readHumanGenome()
        Input parameter: input_file_pointer - pointer to an input file
        Output parameter: none
    */
    void readHumanGenome(ifstream &input_file_pointer);

    /*
        Function name: assess_human_genome()
        Input parameter: inutp_file_pointer - pointer to an input file
        Output parameter: none
    */
    void assessHumanGenome(ifstream &input_file_pointer);

    // Destructor
    ~GENOMEPROCESSING();
};

#endif
