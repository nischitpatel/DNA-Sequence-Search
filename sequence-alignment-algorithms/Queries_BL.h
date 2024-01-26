/*
    Author: Nischit Bipinbhai Patel
    NAU ID#: 6293990
    Course: INF503 Large Scale Data Structures
*/

#ifndef QUERIES_BL_H
#define QUERIES_BL_H

#include "genome_processing.h"

#define HT_SIZE 60000000
// #define HT_SIZE 60
#define SEED_SIZE 11
#define HEADER '>'
#define NULL_CHAR '\0'
#define FRAGMENT_LENGTH 16

// Structure of node
struct Node
{
    // Array to store last 8 characters of fragments
    char fragment[SEED_SIZE + 1];

    long long index;

    // Pointer to next node in a linked list
    struct Node *next;
};

// Structure of linked list
struct LinkedList
{
    // Pointer that will point to first node
    struct Node *head;

    LinkedList() : head(nullptr) {}
};

class Queries_BL
{
    private:
        // Size of fragments
        int nmer;

        // Variable to store size of query dataset
        long long size_of_query_dataset;

        // Hash table
        struct LinkedList *hash_table;

        int gap, match, mismatch; 

    public:
        // Constructor
        Queries_BL();

        // Destructor
        ~Queries_BL();

        // Insert a query in hash table
        void insertInHashTable(char *query, long long index_in_query_dataset);

        // Get radix value
        long long getRadixValue(char *query);

        // Get query dataset in hash table
        void getQueryDatasetInHashTable(char **query_dataset, long long size_of_query_dataset);

        char *search(char **query_dataset, char *query);

        int needlemanWunsch(char *query_fragment, char *fragment);
};

#endif
