/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large scale data structures
*/

/*
    Example of command to run : ./main human_reads_2.fa human.txt binary 10000
    Where:
        ./main : executable .o file
        human_reads_2.fa : queries data file path
        human.txt : genome data file path
        binary : command for how to search (if want to search linearly then provide "linear" in command)
        10000 : fragments counts
*/

// Pre-processors
#include <iostream>
#include <time.h>
#include <iomanip>
#include "../helpers/genome_processing.h"
#include "queries_ar.h"
#include "../helpers/my_strings.h"

using namespace std;

/*
    Main block
    Input arguments:
        1) file path to genome data file
        2) file path to queries data file
        3) sorted/unsorted
        4) fragments counts i.e. 10000, 100K, 1M
*/
int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cout << endl
             << "Usage : " << argv[0]
             << " <file_path_for_query_file>"
             << " <file_path_for_genome_file>"
             << " <command (linear/binary)>"
             << " <fragment_count>" << endl;
    }

    else
    {
        // File paths from arguments
        char const *queries_file_path = argv[1],
                   *genome_file_path = argv[2];

        // Create input file pointers
        ifstream query_file_ptr(queries_file_path),
            genome_file_ptr(genome_file_path);

        // Create an instance of GENOMEPROCESSING
        GENOMEPROCESSING *genome_processing_instance = new GENOMEPROCESSING();

        // Read genome data
        genome_processing_instance->readHumanGenome(genome_file_ptr);

        // Set the genome_data character array
        char *genome_data = genome_processing_instance->getGenomeData();

        // Set the size to genome data size
        long long size = genome_processing_instance->getGenomeSize();

        // Create an instance of Query_AR
        Queries_AR *queries_instance = new Queries_AR(query_file_ptr, genome_data, size);

        // Read queries fromquery data file
        queries_instance->readFromFile(query_file_ptr);

        // Get the search command from arguments i.e. linear or binary
        char *command = argv[3];

        // Get the fragment counts i.e. 10000, 100k, 1M
        long long fragment_count = stol(argv[4]);

        if (fragment_count == -1)
            // Count all possible fragments of size 32 in genome data file 
            fragment_count = size - 32 + 1;

        cout << endl
             << "Fragment count : " << fragment_count << endl;

        // Variable to store time
        clock_t start_time, end_time;

        char linear[] = "linear";
        char binary[] = "binary";

        if (!strCmp(command, linear))
        {
            cout << endl
                 << "Searching Algorithm : " << command << " search" << endl;

            // Get the start time
            start_time = clock();

            // Search sequences
            queries_instance->search(true, fragment_count);

            // Get the end time
            end_time = clock();
        }

        else if (!strCmp(command, binary))
        {
            cout << endl
                 << "Searching Algorithm : " << command << " search" << endl;

            // Sort queries for binary search
            queries_instance->sort_queries();

            // Get the start time
            start_time = clock();

            // Search sequences
            queries_instance->search(false, fragment_count);

            // Get the end time
            end_time = clock();
        }

        else
        {
            // Inform user that command is incorrect
            cout << endl
                 << "Invalid search command. Please provide linear / binary as search command." << endl;

            return 0;
        }

        // Calculate total runtime
        double runtime = (double(end_time - start_time)) / CLOCKS_PER_SEC;

        cout << endl
             << "Runtime : " << fixed << setprecision(5)
             << runtime << endl;

        // Close a file pointer
        query_file_ptr.close();
    }

    return 0;
}
