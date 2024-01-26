/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large Scale Data Structures
*/

#include <iostream>
#include <fstream>
#include <time.h>
#include "prefix_trie.h"
#include "../helpers/genome_processing.h"
#include "../helpers/my_strings.h"

/*
    argv[1] - path to genome file
    argv[2] - number of queries 5000/50000/100000/1000000
    argv[3] - length of subject 50000
    argv[4] - error flag 0/1
*/

int main(int argc, char *argv[])
{
    srand(time(NULL));

    char *genome_file_path = argv[1];
    long long query_count = atoll(argv[2]);
    long random_subject_length = atoll(argv[3]); 
    int flag_error = atoi(argv[4]);

    cout << "--------------------------------------------------" << endl;
    if(!flag_error)
        cout << "           PART A : BASIC PREFIX TRIE" << endl;
    else
        cout << "      PART B : IMPACT OF ERROR RATE ON TRIE" << endl;
    cout << "--------------------------------------------------" << endl << endl;
    cout << "Query count: " << query_count << endl;
    // Read genome file
    ifstream genome_file_ptr(genome_file_path);
    if (!genome_file_ptr.is_open())
    {
        cout << "Error: Unable to open genome file" << endl;
        return 0;
    }

    // instance of genome_processing class
    GENOMEPROCESSING genome_processor;

    cout << "Reading genome file..." << endl;
    genome_processor.readHumanGenome(genome_file_ptr);

    long long genome_length = genome_processor.getGenomeSize();

    char *genome = genome_processor.getGenomeData();

    char* random_subject = new char[random_subject_length];

    // Generate random subject
    long long start_index = rand() % (genome_length - random_subject_length);
    for (long long i = 0; i < random_subject_length; i++)
    {
        random_subject[i] = genome[start_index + i];
        // random_subject[i] = genome[i];
    }

    // instance of prefix_trie class
    Prefix_Trie prefix_trie;

    // Build prefix trie
    prefix_trie.buildPrefixTrie(random_subject, random_subject_length, query_count, flag_error);

    // Search each possible 36-mer of random subject in the prefix trie
    long long hits=0;
    char *query = new char[36 + 1];
    for(long long i = 0; i < random_subject_length - 36 + 1; i++)
    {
        // Read 36-mer query
        for(long long j = 0; j < 36; j++)
        {
            query[j] = random_subject[i + j];
        }
        query[36] = '\0';

        // Search query in the prefix trie
        hits += prefix_trie.search(query);
    }

    cout << "Hits: " << hits << endl << endl;

    cout << "##############################################################################" << endl << endl;

    delete[] query;
    delete[] random_subject;

    return 0;
}