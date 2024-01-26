/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large Scale Data Structures
*/

#ifndef QUERIES_NW_H
#define QUERIES_NW_H

#include "../helpers/genome_processing.h"

#define HEADER '>'
#define NULL_CHAR '\0'

class Queries_NW
{
    private:
        // Path for a query data file
        char *query_data_file_path;

        // Size of fragments
        int nmer;

        // Variable to store size of query dataset
        long long size_of_query_dataset;

        // 2D array to store fragments of query dataset
        char **query_dataset;

        int gap, match, mismatch;

    public:
        // Subject dataset with n fragments
        char **subject;

        // Constructor
        Queries_NW(char *file_path, int fragment_length);

        // Destructor
        ~Queries_NW();

        char **getQueryDataset();

        long long getSizeOfQuery();

        void getQueryDatasetIn2dArray();

        // Needleman Wunsch Algorithm
        int nw(char *query_fragment, char *subject_fragment);

        // Search for fragments in query dataset and return best fragment
        char *search(char* query, int allowed_mismatches);

       // Get the size of query dataset
       long long getSizeOfQueryDataset(char *query_data_file_path);
};
#endif
