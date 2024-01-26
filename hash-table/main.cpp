/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large scale data structures
*/

// Pre-processors
#include <iostream>
#include <stdlib.h>
#include "queries_ht.h"
#include "../helpers/genome_processing.h"
#include "../helpers/my_strings.h"

using namespace std;

/*
    <./executable_file> <query_file_path> <genome_file_path> <command> <hash_table_size>
*/

// Main block
int main(int argc, char *argv[])
{
    // If command is not correct
    if (argc < 5)
    {
        cout << endl
             << "Command to execute : <./executable_file> <query_file_path> <genome_file_path> <command> <hash_table_size>"
             << endl
             << "command :" << endl
             << "search_time - to get time to search all possible fragments" << endl
             << "assess - to get a time to populate hashtable of different sizes" << endl
             << "hash_table_size : 1000000 / 10000000 / 30000000 / 60000000" << endl;

        return 1;
    }

    // Get file paths
    char const *query_file_path = argv[1];
    char const *genome_file_path = argv[2];

    // Get command
    char *command = argv[3];
    cout << endl << "Command : " <<  command << endl << endl;

    // Get the size of hash table
    unsigned int hash_table_size = strtoul(argv[4], NULL, 10);

    // Open files
    ifstream query_file_ptr(query_file_path),
        genome_file_ptr(genome_file_path);

    // Create an instance of GENOMEPROCESSING
    GENOMEPROCESSING *genome_processing_instance = new GENOMEPROCESSING();

    // Read genome data
    genome_processing_instance->readHumanGenome(genome_file_ptr);

    // Set the genome_data character array
    char *genome_data = genome_processing_instance->getGenomeData();

    // Set the size to genome data size
    long long genome_data_size = genome_processing_instance->getGenomeSize();

    // Create an instance of Queries_HT
    Queries_HT *queries_ht_instance = new Queries_HT(hash_table_size);
	
    char assess_cmd[] = "assess";

    char search_speed_cmd[] = "search_time";

    // If command is assess
    if (strCmp(command, assess_cmd) == 0)
    {
        // Create hash table
        queries_ht_instance->assess(query_file_ptr);
    }
    
    // If command is search_time
    else if (strCmp(command, search_speed_cmd) == 0)
    {
        // Count total number of possible fragments
        long long int fragments_count = genome_data_size - FRAGMENT_LENGTH + 1;

        // Create hash table
        queries_ht_instance->assess(query_file_ptr);

        // Search all queries in hash table
        queries_ht_instance->searchSpeed(genome_data, fragments_count);
    }

    else
    {
        cout << endl
             << "Invalid command! Command must be : assess/search_time" << endl;
    }

    // Delete instances
    delete genome_processing_instance;
    delete queries_ht_instance;

    // Close files
    query_file_ptr.close();
    genome_file_ptr.close();

    return 0;
}
