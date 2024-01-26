/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large Scale Data Structures
*/

// Pre-processors
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "Queries_NW.h"
#include "Queries_BL.h"
#include "../helpers/genome_processing.h"
#include "../helpers/my_strings.h"

/*
    Command:
        ./<executable_file> <query_file_path> <subject_file_path> <length_of_fragment/nmer> <command> <fragments_count>

    Example:
        <length_of_fragment/nmer> = 16
        <command> = search/random/blast/blast_random
        <fragments_count> = 10000/100000/1000000
*/

char randomBase()
{
    int random_number = rand() % 5;

    switch (random_number)
    {
        case 0:
            return 'A';
        case 1:
            return 'C';
        case 2:
            return 'G';
        case 3:
            return 'T';
        case 4:
            return 'N';
    }
}

// Main function
int main(int argc, char *argv[])
{
    // Get the arguments from command line
    char* query_file_path = argv[1];
    char* subject_file_path = argv[2];
    int nmer = atoi(argv[3]);
    char* command = argv[4];
    long long fragments_count = atol(argv[5]);

    cout << "Getting the size of query dataset..." << endl;

    Queries_NW queries_nw(argv[1], nmer);

    // Reading queries
    cout << "Reading query dataset..." << endl;
    queries_nw.getQueryDatasetIn2dArray();

    cout << "Created 2D array of query dataset" << endl;

    // Subject array to store random fragments
    char** subject = new char*[fragments_count];

    Queries_BL queries_bl;
    long long query_file_size = queries_nw.getSizeOfQuery();
    char **query_dataset = queries_nw.getQueryDataset();

    // Start and end time
    clock_t start, end;

    int blast_flag = 0;

    if(!strCmp(command, "blast") || !strCmp(command, "blast_random")) 
    {
        blast_flag = 1;
    }

    // If command is to search random fragments from genome dataset
    if(!strCmp(command, "search") || !strCmp(command, "blast"))
    {
        // Reading subject
        GENOMEPROCESSING genome_processing;
        ifstream genome_file(argv[2]);
        if(!genome_file.is_open())
        {
            cout << "Error: Unable to open file" << endl;
            return 0;
        }

        genome_processing.readHumanGenome(genome_file);

        long long genome_length = genome_processing.getGenomeSize();

        char* genome_data = genome_processing.getGenomeData();

        // Get random fragments
        cout << "Getting random fragments from genome data file..." << endl;

        srand(time(NULL));

        for(long long j=0; j<fragments_count; j++) 
        {
            long long index = rand() % (genome_length - nmer);

            subject[j] = new char[17];

            for(long long i=0; i<16; i++) 
                subject[j][i] = genome_data[j+i];

            subject[j][16] = NULL_CHAR;
        }
    }

    else if (!strCmp(command, "random") || !strCmp(command, "blast_random"))
    {
        cout << "Creating completely random fragments..." << endl;

        // Creating random fragments
        srand(time(NULL));

        for(long long i=0; i<fragments_count; i++)
        {
            subject[i] = new char[nmer+1];

            for(int j=0; j<nmer; j++)
                subject[i][j] = randomBase();

            subject[i][nmer] = NULL_CHAR;
        }
    }

    else
    {
        cout << "Error: Invalid command" << endl;
        return 0;
    }

    // for(long long i=0; i<fragments_count; i++)
    //     cout << i << " " << subject[i] << endl;
        
        // queries_bl.getQueryDatasetInHashTable(query_dataset, query_file_size);

    // Best match
    char* best_match;

    // Number of hits
    long long hits = 0;

    // Start time
    start = clock();

    int count = 5;

    // Fuzzy search using needleman-wunsch algorithm
    if (!blast_flag)
    {
        cout << "Searching for fragments..." << endl;

        for(long long i=0; i<fragments_count; i++)
        {
            // cout << "Searching for " << i << endl;
            best_match = NULL;
            // if (blast_flag)
            //     best_match = queries_bl.search(query_dataset, subject[i]);
            
            // else
                best_match = queries_nw.search(subject[i], 2);
                
            if(best_match != NULL) hits++;
        }
    }
    // Fuzzy search using BLAST
    else
    {
        // Create hash table
        cout << "Creating hash table..." << endl;
        queries_bl.getQueryDatasetInHashTable(subject, fragments_count);

        cout << "Searching for fragments..." << endl;

        for(long long i=0; i<query_file_size; i++)
        {
            // cout << i << "    ";
            best_match = NULL;

            best_match = queries_bl.search(subject, query_dataset[i]);

            if(best_match != NULL) hits++;

            // cout << "\x1B[1A";
        }
    }

    // End time
    end = clock();

    cout << "Total hits: " << hits << endl;

    cout << "Time taken to search " << fragments_count << "fragments in query dataset: " << (double)(end - start)/CLOCKS_PER_SEC << " seconds" << endl;

    // Free manually allocated memory
    for(long long i=0; i<fragments_count; i++) delete[] subject[i];
    delete[] subject;

    return 0;
}