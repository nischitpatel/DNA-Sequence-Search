/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large scale data structures
*/

#ifndef QUERIES_HT_H
#define QUERIES_HT_H

#include <fstream>

#define FRAGMENT_LENGTH 16
#define NULL_CHAR '\0'
#define HEADER '>'

// Structure of node
struct Node
{
    // Array to store last 8 characters of fragments
    char fragment[FRAGMENT_LENGTH + 1];

    // Pointer to next node in a linked list
    struct Node *next;
};

// Structure of linked list
struct LinkedList
{
    // Pointer that will point to first node
    struct Node *head;

    // Pointer that will point to last node
    struct Node *tail;

    LinkedList() : head(nullptr), tail(nullptr) {}
};

class Queries_HT
{
private:
    // Size of hash table
    unsigned int m;

    // Hash table
    struct LinkedList *hashTable;

public:
    // Constructor
    Queries_HT(unsigned int size);

    // Function to search in a hash table
    bool searchInHashTable(char *query);

    // Insert in a hash table
    bool insertInHashTable(char *query);

    // Get radix value
    long getRadixValue(char *query);

    // Get index of hash table
    unsigned int getHashTableIndex(unsigned int value);

    // Assess
    void assess(std::ifstream &fileptr);

    // Searching speen
    void searchSpeed(char *genome, long long fragments_count);

    // Destructor
    ~Queries_HT();
};

#endif
