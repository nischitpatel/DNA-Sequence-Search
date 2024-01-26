/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large scale data structures
*/

// Pre-processors
#include <iostream>
#include <iomanip>
#include "queries_ar.h"
#include "my_strings.h"

using namespace std;

// Default constructor
Queries_AR::Queries_AR()
{
    total_genome_queries = 0;

    genome_query_length = 32;

    genome_size = 0;

    genome_data = NULL;

    genome_queries = NULL;
}

// Custom constructor
Queries_AR::Queries_AR(ifstream &fileptr, char *genome, long long size) : Queries_AR()
{
    // Set genome size
    genome_size = size;

    // Set genome data array
    genome_data = genome;

    // Check if file is open or not
    if (fileptr.is_open())
    {
        string line;

        long long int line_count = 0;

        // Calculate queries in the read file
        while (fileptr >> line)
            if (line[0] == HEADER)
                line_count++;

        // Set total_genome_queries
        total_genome_queries = line_count;

        // Create an array of array to store genome queries
        genome_queries = new char *[total_genome_queries];
    }
}

/*
    Function name: read_queries()
    Input data: fileptr - pointer to read file
    Output data: None
*/
void Queries_AR::readFromFile(ifstream &fileptr)
{
    // Check if file is open or not
    if (fileptr.is_open())
    {
        fileptr.clear();

        // Set the file pointer to the begining of a file
        fileptr.seekg(0, ios::beg);

        cout << endl
             << "Reading queries ... " << endl;

        string line;

        long long index = 0;

        // Read queries and store in 2D array genome_queries
        while (getline(fileptr, line))
        {
            if (line[0] != HEADER)
            {
                genome_queries[index] = new char[genome_query_length + 1];

                for (int j = 0; j < genome_query_length; j++)
                    genome_queries[index][j] = line[j];

                genome_queries[index][genome_query_length] = NULL_CHAR;

                index++;
            }
        }
    }

    cout << endl
         << "Total genome queries : " << total_genome_queries << endl;
}

/*
    Function name: merge()
    Input data: **genome_queries - 2D array of queries
                beg - begining index of the array
                mid - mid index of the array
                end - last index of the array
    Output data(return): None
*/
void Queries_AR::merge(char **genome_queries, long long start, long long mid, long long end)
{
    // Get the size of left subarray and right subarray
    long long left_array_size = mid - start + 1,
              right_array_size = end - mid;

    // Create 2D arrays for left subarray and right subarray
    char **left_array = new char *[left_array_size],
         **right_array = new char *[right_array_size];

    for (long long i = 0; i < left_array_size; i++)
        left_array[i] = genome_queries[start + i];

    for (long long j = 0; j < right_array_size; j++)
        right_array[j] = genome_queries[mid + 1 + j];

    // Declare and initialize indexes of left, right subarrays and merged array
    long long left_arr_index = 0, right_arr_index = 0, merged_arr_index = start;

    // Compare and merge arrays in genome_queries
    while (left_arr_index < left_array_size && right_arr_index < right_array_size)
    {
        if (strCmp(left_array[left_arr_index], right_array[right_arr_index]) < 0)
            genome_queries[merged_arr_index++] = left_array[left_arr_index++];

        else
            genome_queries[merged_arr_index++] = right_array[right_arr_index++];
    }

    // Add left elements of left array in genome_queries
    while (left_arr_index < left_array_size)
        genome_queries[merged_arr_index++] = left_array[left_arr_index++];

    // Add left elements of right array in genome_queries
    while (right_arr_index < right_array_size)
        genome_queries[merged_arr_index++] = right_array[right_arr_index++];
}

/*
    Function name: merge_sort()
    Input data: **genome_queries - 2D array of queries
                beg - begining index of the array
                end - last index of the array
    Output data(return): None
*/
void Queries_AR::merge_sort(char **genome_queries, long long start, long long end)
{
    // Breaking condition
    if (start >= end)
        return;

    // Get the middle index of an array
    long long mid = (start + (end - start) / 2);

    // Recursive call on left subarrays
    merge_sort(genome_queries, start, mid);

    // Recursive call on right subarrays
    merge_sort(genome_queries, mid + 1, end);

    // Function call to sort and merge arrays
    merge(genome_queries, start, mid, end);
}

/*
    Function name: sort_queries()
    Input data: None
    Output data (return): None
    Output data (parameter): lexographically sorted genome_queries 2D array
*/
void Queries_AR::sort_queries()
{
    // Call merge_sort function to sort 2D array
    merge_sort(genome_queries, 0, total_genome_queries - 1);
}

/*
    Function name: linear_search()
    Input data: *sequence - array of sequence to search
    Output data: 1 - if sequence found
                    0 - otherwise
*/
long long int Queries_AR::linear_search(char *sequence)
{
    for (long long i = 0; i < total_genome_queries; i++)
        // If sequence found then return true
        if (strCmp(sequence, genome_queries[i]) == 0)
        {
            return i;
        }

    // If sequence not found then return false
    return -1;
}

/*
    Function name: binary_search()
    Input data: *sequence - array of sequence to search
    Output data: 1 - if sequence found
                    0 - otherwise
*/
long long int Queries_AR::binary_search(char *sequence)
{
    long long start = 0, end = total_genome_queries - 1, mid, match;

    while (start <= end)
    {
        mid = start + (end - start) / 2;

        match = strCmp(genome_queries[mid], sequence);

        // If sequence found then return true
        if (match == 0)
        {
            return mid;
        }

        else if (match > 0)
            end = mid - 1;

        else
            start = mid + 1;
    }

    // If sequence not found then return false
    return -1;
}

/*
    Function name: search()
    Input data: is_linear_search (bool) - flag for linear search
                subject_fragments_count (long long) - count of fragments
    Output data: None
*/
void Queries_AR::search(bool is_linear_search, long long subject_fragments_count)
{
    long long int match = -1;
    
    char *sequence = new char[genome_query_length + 1];

    int match_count = 10;

    cout << endl
         << "First 10 queries : " << endl
         << endl;
    cout << left << setw(20) << "Query file index" << setw(60) << "Sequence" << setw(10) << "Genome file index"<< endl; 
    for (long long i = 0; i < subject_fragments_count + genome_query_length; i++)
    {
        // Get the sequence of 32 characters in sequence array
        for (int j = 0; j < genome_query_length; j++)
        {
            sequence[j] = genome_data[j + i];
        }

        // End the sequence with NULL character
        sequence[genome_query_length] = NULL_CHAR;

        match = is_linear_search ? linear_search(sequence) : binary_search(sequence);

        // If match is found then print first 10 sequences
        if (match != -1 && match_count > 0)
        {
    	    cout << left << setw(20) << match << setw(60) << sequence << setw(10) << i << endl;
            match_count--;
        }

        // set match to -1 again
        match = -1;
    }
}

// Destructor to delete 2D array
Queries_AR::~Queries_AR()
{
    for (long long i = 0; i < total_genome_queries; i++)
        delete[] genome_queries[i];

    delete[] genome_queries;
}
