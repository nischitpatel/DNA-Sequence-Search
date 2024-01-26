/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large Scale Data Structures
*/

// Pre-processors
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <limits.h>
#include <iomanip>
#include <omp.h>
#include "../helpers/my_strings.h"
#include "../helpers/genome_processing.h"
#include "Queries_NW.h"

using namespace std;

// Constructor
Queries_NW::Queries_NW(char *file_path, int fragment_length)
{
    srand(time(NULL));

    // Initialize path for a query data file
    query_data_file_path = file_path;

    // Initialize length of fragment
    nmer = fragment_length;

    // Initialize size of query dataset
    size_of_query_dataset = getSizeOfQueryDataset(query_data_file_path);

    query_dataset = new char *[size_of_query_dataset];

    // Initialize 2D array to store fragments of query dataset
    for (long long i = 0; i < size_of_query_dataset; i++)
        query_dataset[i] = new char[17];

    // Initialize gap, match, mismatch, and allowed mismatches
    gap = -1;
    match = 2;
    mismatch = -1; 
    // allowed_mismatches = 2;
}

char **Queries_NW::getQueryDataset()
{
    return query_dataset;
}

long long Queries_NW::getSizeOfQuery()
{
    return size_of_query_dataset;
}

/*
    @brief: getSizeOfQueryDataset()
    @param: query_data_file_path
    @return: size_of_query_dataset
    @description: This function returns size of query dataset
*/
long long Queries_NW::getSizeOfQueryDataset(char *query_data_file_path)
{
    // Initialize size of query dataset
    long long size_of_query_dataset = 0;

    // Open query data file
    ifstream query_data_file(query_data_file_path);

    // Check if query data file is open
    if (query_data_file.is_open())
    {
        // Read query data file line by line
        string line;
        while (getline(query_data_file, line))
        {
            if (line[0] != HEADER)
                // Increment size of query dataset
                size_of_query_dataset++;
        }
    }

    // Close query data file
    query_data_file.close();

    // Return size of query dataset
    return size_of_query_dataset;
}

/*
    @brief: getQueryDatasetIn2dArray()
    @param: None
    @return: None
    @description: This function reads query dataset in a 2D array data structure
*/
void Queries_NW::getQueryDatasetIn2dArray()
{
    // Open query data file
    ifstream query_data_file(query_data_file_path);

    query_data_file.clear();
    query_data_file.seekg(0, ios::beg);

    // Check if query data file is open
    if (query_data_file.is_open())
    {
        // Initialize index for 2D array to store fragments of query dataset
        long long index = 0;

        // Read query data file line by line
        string line;
        while (getline(query_data_file, line))
        {
            // Check if line is not a header
            if (line[0] != HEADER)
            {
                // Store fragment in 2D array to store fragments of query dataset
                for (int i = 0; line[i] != NULL_CHAR; i++)
                    query_dataset[index][i] = line[i];
                query_dataset[index][16] = NULL_CHAR;

                // Increment index for 2D array to store fragments of query dataset
                index++;
            }
        }
    }

    // Close query data file
    query_data_file.close();
}

/*
    @brief: nw()
    @param: query_fragment, subject_fragment
    @return: similarity_score
    @description: This function implements Needleman Wunsch Algorithm
*/
int Queries_NW::nw(char *query_fragment, char *fragment)
{
    // Initialize matrix
    int **matrix = new int *[17];

    for (int i = 0; i < 17; i++)
        matrix[i] = new int[nmer + 1];

    int m, gap_left, gap_up, mismatch_flag = 0, mismatch_count = 0;

    matrix[0][0] = 0;

    // Initialize first row and first column with gap penalty
    for (int i = 1; i < 17; i++)
    {
        matrix[i][0] = matrix[i - 1][0] + gap;
    }
    for(int i=1; i<nmer+1; i++)
    {
        matrix[0][i] = matrix[0][i-1] + gap;
    }

    // Fill the matrix
    for (int i = 1; i < 17; i++)
    {
        for (int j = 1; j < nmer + 1; j++)
        {
            if (query_fragment[i - 1] == fragment[j - 1])
                m = matrix[i - 1][j - 1] + match;
            else
                m = matrix[i - 1][j - 1] + mismatch;

            gap_left = matrix[i][j - 1] + gap;
            gap_up = matrix[i - 1][j] + gap;

            if (m >= gap_left && m >= gap_up)
                matrix[i][j] = m;
            else if (gap_left > m && gap_left > gap_up)
                matrix[i][j] = gap_left;
            else
                matrix[i][j] = gap_up;
        }
    }

    // Store similarity score
    int similarity_score = matrix[16][nmer];

    // Delete matrix
    for (int i = 0; i < 17; i++)
        delete[] matrix[i];
    delete[] matrix;

    // Return the similarity score
    return similarity_score;
}

char* Queries_NW::search(char* query, int allowed_mismatches)
{
    int best_similarity_score = 0;

    long long best_similarity_score_index = -1;

    // int similarity_score;
    int run=1;

    int num_of_threads = omp_get_num_procs();

    // Score for each thread
    int *max_scores = new int[num_of_threads];

    // Index of best match for each thread
    long long *max_score_idx = new long long[num_of_threads];

    //cout << query << endl;

    // Initially set score for each thread to 0 and index of best match to -1
    for(int i=0; i<num_of_threads; i++)
    {
        max_scores[i] = 0;
        max_score_idx[i] = -1;
    }

    // Set number of threads
    omp_set_num_threads(num_of_threads);

    // Parallelized for loop
    #pragma omp parallel for
    for(long long j=0; j<size_of_query_dataset; j++)
    {
        int thread_id = omp_get_thread_num();
        // if(best_similarity_score != 32)

        for(int i=0; i<num_of_threads && run; i++)
        {
            // If score is equal to nmer * match, then 
            // there is no need to check further as we got the exact same match
            if(max_scores[i] == nmer * match)
            {
                run = 0;
            }
        }

        if(run)
        {
            int similarity_score = nw(query, query_dataset[j]);

            // Similarity score should greater than or equal to 
            // (nmer - allowed_mismatches) * match to be considered as a match
            if(similarity_score > max_scores[thread_id] && similarity_score >= (nmer - allowed_mismatches) * match + (allowed_mismatches * mismatch))
            {
                max_scores[thread_id] = similarity_score;
                max_score_idx[thread_id] = j;
            }
        }
    }

    // Find the best match from all threads
    for(int i=0; i<num_of_threads; i++)
    {
        if(max_scores[i] > best_similarity_score)
        {
            best_similarity_score = max_scores[i];
            best_similarity_score_index = max_score_idx[i];
        }
    }

    // cout << best_similarity_score << endl;

    // Return NULL if we do not find any match
    if (best_similarity_score_index==-1) return NULL;

    // cout << setw(20) << best_similarity_score;

    // Return the best match
    return query_dataset[best_similarity_score_index];
}

// Destructor
Queries_NW::~Queries_NW()
{
    // Delete 2D array to store fragments of query dataset
    for (long long i = 0; i < size_of_query_dataset; i++)
        delete[] query_dataset[i];
    delete[] query_dataset;
}