/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large scale data structures
*/

#ifndef QUERIES_AR_H
#define QUERIES_AR_H

// Pre-processors
#include <fstream>

using namespace std;

#define NULL_CHAR '\0'
#define HEADER '>'

class Queries_AR
{
private:
    // Character array to store genome data
    char *genome_data;

    // Character 2D array to store queries
    char **genome_queries;

    // Variable to store genome data
    long long genome_size;

    // Variable to store count of genome queries
    long long total_genome_queries;

    // Variable to store length of query
    int genome_query_length;

    /*
        Function name: merge()
        Input data: **genome_queries - 2D array of queries
                    beg - begining index of the array
                    mid - mid index of the array
                    end - last index of the array
        Output data(return): None
    */
    void merge(char **genome_queries, long long start, long long mid, long long end);

    /*
        Function name: merge_sort()
        Input data: **genome_queries - 2D array of queries
                    beg - begining index of the array
                    end - last index of the array
        Output data(return): None
    */
    void merge_sort(char **genome_queries, long long start, long long end);

    /*
        Function name: linear_search()
        Input data: *sequence - array of sequence to search
        Output data: -1 - if not found
                     index - where it is found
    */
    long long int linear_search(char *sequence);

    /*
        Function name: binary_search()
        Input data: *sequence - array of sequence to search
        Output data: -1 - if not found
                     index - where it is found
    */
    long long int binary_search(char *sequence);

public:
    // Default constructor
    Queries_AR();

    // Custom constructor
    Queries_AR(ifstream &fileptr, char *genome, long long size);

    /*
        Function name: readFromFile()
        Input data: fileptr - pointer to read file
        Output data: None 
    */
    void readFromFile(ifstream &fileptr);

    /*
        Function name: search_sequences()
        Input data: is_linear_search (bool) - flag for linear search
                    subject_fragments_count (long long) - count of fragments
        Output data: None 
    */
    void search(bool is_linear_search, long long subject_fragments_count);

    /*
        Function name: sort_queries()
        Input data: None
        Output data (return): None
        Output data (parameter): lexographically sorted genome_queries 2D array
    */
    void sort_queries();

    // Destructor to delete 2D array
    ~Queries_AR();
};

#endif
