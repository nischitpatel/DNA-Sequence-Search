/*
    Author: Nischit Bipinbhai Patel
    NAU ID #: 6293990
    Course: INF503 Large scale data structures
*/

// Pre-processors
#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>
#include "queries_ht.h"
#include "my_strings.h"

using namespace std;

// Constructor
Queries_HT::Queries_HT(unsigned int size)
{
    // Set the size of hash table 'm'
    m = size;

    // Array of linked list
    hashTable = new LinkedList[m];
}

/*
    Function name: getHashTableIndex()
    Input parameter: value - radix value
    Output parameter(return): Index of hash table based on radix value
                              and size of hash table
*/
unsigned int Queries_HT::getHashTableIndex(unsigned int value)
{
    // Find index of hash table
    // unsigned int index = value % m;

    // Return the index in range 0 to m
    return value % m;
}

/*
    Function name: getRadixValue()
    Input parameter: query - query to calculate radix value
    Output parameter(return): radix_value - radix value of the query
*/
// unsigned int Queries_HT::getRadixValue(char *query)
long Queries_HT::getRadixValue(char *query)
{
    // Set the radix_value to 0
    long radix_value = 0;

    // Set the base to 5 as we have 5 characters in our universe
    // { A, C, G, T, N }
    unsigned int base = 5;

    int index = 0;

    // Get the character from the fragment and add digit
    // while (query[index] != NULL_CHAR)
    // while (index < FRAGMENT_LENGTH / 2)
    while (index < FRAGMENT_LENGTH)
    {
        char c = query[index];

        unsigned int int_representation;

        switch (c)
        {
        case 'A':
            int_representation = 0;
            break;
        case 'C':
            int_representation = 1;
            break;
        case 'G':
            int_representation = 2;
            break;
        case 'T':
            int_representation = 3;
            break;
            // case 'N':
            // int_representation = 4;
            // break;
        default:
            int_representation = 4;
            break;
        }

        // Update radix_value variable
        long power = pow(base, (FRAGMENT_LENGTH) - index - 1);

        radix_value += int_representation * power; // pow(base, (FRAGMENT_LENGTH / 2) - index - 1);

        index++;
    }

    // Return the radix value
    return radix_value;
}

/*
    Function name: searchInHashTable()
    Input parameter: query - query to search for
    Output parameter(return): true - if query found
                              false - otherwise
*/
bool Queries_HT::searchInHashTable(char *query)
{
    // Get the radix value of first 8 characters in the query
    unsigned int value = getRadixValue(query);

    // Get the index of the hashtable
    unsigned int index = getHashTableIndex(value);

    // If nothing is at index then return false
    if (hashTable[index].head == nullptr)
        return false;

    // Check in the linked list
    Node *temp = hashTable[index].head;

    // cout << endl << "in search" << temp->fragment << endl << query + (FRAGMENT_LENGTH/2) << endl;

    // char last_8_chars[9];

    // for (int i = 8; i < 16; i++)
    // {
    //     last_8_chars[i - 8] = query[i];
    // }

    // last_8_chars[9] = NULL_CHAR;

    while (temp != nullptr)
    {
        // If found then return true
        // if (!strCmp(temp->fragment, last_8_chars))
        if(!strcmp(temp->fragment, query))
        {
            // cout << endl << temp->fragment << endl << query << endl;
            // cout << query << " found @ " << index;
            return true;
        }

        // Go to the next node in the linked list
        temp = temp->next;
    }
    // cout << endl << "false" << endl;
    //  Not found
    return false;
}

/*
    Function name: insertInHashTable()
    Input parameter: query - query to insert in a hash table
    Output parameter(return): true - if collision occurs
                              false - otherwise
*/
bool Queries_HT::insertInHashTable(char *query)
{
    // Create a node for linked list
    Node *node = new Node;

    // Store query in fragment
    // node->fragment = query + (FRAGMENT_LENGTH / 2);

    for (int i = 0; i < FRAGMENT_LENGTH; i++)
    {
        node->fragment[i] = query[i];
    }

    node->fragment[FRAGMENT_LENGTH] = NULL_CHAR;

    // Set the next of node to nullptr
    node->next = nullptr;

    // Get the radix value
    long value = getRadixValue(query);

    // Get the index of hash table
    unsigned int index = getHashTableIndex(value);

    // No collision
    if (hashTable[index].head == nullptr && hashTable[index].tail == nullptr)
    {
        hashTable[index].head = node;
        hashTable[index].tail = node;

        return false;
    }

    // Add a new node at the end of the linked list
    hashTable[index].tail->next = node;
    hashTable[index].tail = node;

    // Collision found
    return true;
}

/*
    Function name: assess()
    Input parameter: fileptr - pointer to a file
    Output parameter(return): none
*/
void Queries_HT::assess(std::ifstream &fileptr)
{
    if (fileptr.is_open())
    {
        // Clear the file pointer
        fileptr.clear();

        // Set the file pointer at the begining of the file
        fileptr.seekg(0, ios::beg);

        cout << endl
             << "Creating hash table of size : " << m << endl;

        string line;

        char query_to_insert_in_hash_table[FRAGMENT_LENGTH + 1];

        unsigned int collision_count = 0;

        long long int queries_count = 0;

        // Get the start time
        time_t start_time = clock();

        while (getline(fileptr, line))
        {
            if (line[0] != HEADER)
            {
                // Increment queries count by 1
                queries_count++;

                int i = 0;

                while (line[i] != NULL_CHAR)
                {
                    query_to_insert_in_hash_table[i] = line[i];
                    i++;
                }

                query_to_insert_in_hash_table[i] = NULL_CHAR;

                // Insert a fragment into a hash table and increment collision count accordingly
                if (insertInHashTable(query_to_insert_in_hash_table))
                    collision_count++;
            }
        }

        // Get the end time
        time_t end_time = clock();

        cout << endl
             << "Hash table creation successful !" << endl;

        cout << endl
             << "Total queries in a read file : " << queries_count << endl;

        cout << endl
             << "Total collisions occurred : " << collision_count << endl;

        cout << endl
             << "Time required to populate the hash table : "
             << fixed << setprecision(5) << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
    }
}

/*
    Function name: searchSpeed()
    Input parameter: genome - character array of genome data
                     fragments_count - total number of possible fragments
    Output parameter(return): none
*/
void Queries_HT::searchSpeed(char *genome, long long fragments_count)
{
    // Variables to store time
    time_t start_time, end_time;

    // Variable to store match counts
    int match_count = 15;

    long long int total_queries_found = 0;

    // Character array to store fragment to be searched
    char *fragment = new char[FRAGMENT_LENGTH + 1];

    cout << endl
         << "First 15 fragments : " << endl;

    cout << endl
         << left << setw(20) << "Genome File Index" << setw(40) << "Sequence" << endl;

    // Get the start time
    start_time = clock();

    // Find all possible fragments and search in hash table
    for (long long i = 0; i < fragments_count; i++)
    {
        // Copy 16 characters fragment in fragment array
        for (long long j = 0; j < FRAGMENT_LENGTH; j++)
        {
            fragment[j] = genome[j + i];
        }

        // End the fragment with null character i.e. '\0'
        fragment[FRAGMENT_LENGTH] = NULL_CHAR;

        bool match = searchInHashTable(fragment);

        // If match is found then increment total_queries_found by 1
        if (match)
        {
            // cout << "\r";
            // cout.flush();
            total_queries_found++;

            // If match_count > 0 then print query with index in subject dataset
            if (match_count > 0)
            {
                // Print query
                cout << left << setw(20) << i << setw(40) << fragment << endl;

                // Decrement match_count by 1
                match_count--;
            }

            // cout << total_queries_found;
        }
    }

    delete[] fragment;

    // Get the end time
    end_time = clock();

    cout << endl
         << "Total queries found : " << total_queries_found << endl;

    cout << endl
         << "Time required to search " << fragments_count << " fragments : "
         << fixed << setprecision(5) << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
}

// Destructor
Queries_HT::~Queries_HT()
{
    // Delete linked list at each index
    Node *temp;

    for (int i = 0; i < m; i++)
    {
        temp = hashTable[i].head;

        while (hashTable[i].head != nullptr)
        {
            temp = hashTable[i].head;

            hashTable[i].head = hashTable[i].head->next;

            delete temp;
        }
    }

    // Delete array
    delete[] hashTable;
}
