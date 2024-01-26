/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large Scale Data Structures
    NAU ID #: 6293990
*/

#include <iostream>
#include <fstream>
#include "prefix_trie.h"

using namespace std;

// Constructor
Prefix_Trie::Prefix_Trie()
{
    root = new Node;
}

// Custom constructor
Prefix_Trie::Prefix_Trie(char *subject, long long subject_length, long query_count, int flag_error)
{
    root = new Node;
    buildPrefixTrie(subject, subject_length, query_count, flag_error);
}

// Copy constructor
Prefix_Trie::Prefix_Trie(const Prefix_Trie &other)
{
    root = copyTrie(other.root);
}

// Copy trie
Node *Prefix_Trie::copyTrie(Node *node)
{
    if (node == nullptr)
        return nullptr;

    Node *newNode = new Node;

    newNode->next[A] = copyTrie(node->next[A]);
    newNode->next[C] = copyTrie(node->next[C]);
    newNode->next[G] = copyTrie(node->next[G]);
    newNode->next[T] = copyTrie(node->next[T]);
    newNode->next[N] = copyTrie(node->next[N]);

    return newNode;
}

// Destructor
Prefix_Trie::~Prefix_Trie()
{
    deleteTrie(root);
}

/*
    Function: deleteTrie
    Purpose: Delete a trie
    Parameters: Node* node - root of the trie to be deleted
    Returns: void
    Time Complexity: O(n) where n is the number of nodes in the trie
*/
void Prefix_Trie::deleteTrie(Node *node)
{
    if (node == nullptr)
        return;

    deleteTrie(node->next[A]);
    deleteTrie(node->next[C]);
    deleteTrie(node->next[G]);
    deleteTrie(node->next[T]);
    deleteTrie(node->next[N]);

    delete node;
}

/*
    Function: insert
    Purpose: Insert a query into the trie
    Parameters: char* query - query to be inserted
    Returns: void
    Time Complexity: O(n) where n is the length of the query
*/
long Prefix_Trie::insert(char *query)
{
    Node *current = root;
    long nodes = 0;
    while (*query != '\0')
    {
        switch (*query)
        {
        case 'A':
            if (current->next[A] == nullptr)
            {
                current->next[A] = new Node;
                nodes++;
            }
            current = current->next[A];
            break;
        case 'C':
            if (current->next[C] == nullptr)
            {
                current->next[C] = new Node;
                nodes++;
            }
            current = current->next[C];
            break;
        case 'G':
            if (current->next[G] == nullptr)
            {
                current->next[G] = new Node;
                nodes++;
            }
            current = current->next[G];
            break;
        case 'T':
            if (current->next[T] == nullptr)
            {
                current->next[T] = new Node;
                nodes++;
            }
            current = current->next[T];
            break;
        case 'N':
            if (current->next[N] == nullptr)
            {
                current->next[N] = new Node;
                nodes++;
            }
            current = current->next[N];
            break;
        }
        query++;
    }
    // current->query_occured++;
    return nodes;
}

long Prefix_Trie::search(char *query)
{
    return searchWithMismatches(root, query, ALLOWED_MISMATCHES);
}

long Prefix_Trie::searchWithMismatches(Node *node, char *query, int mismatches_left)
{
    if (node == nullptr)
        return 0;

    if (*query == '\0')
        return 1;
        // return node->query_occured;

    Node *next_node = nullptr;

    int index;

    switch (*query)
    {
    case 'A':
        index = A;
        break;
    case 'C':
        index = C;
        break;
    case 'G':
        index = G;
        break;
    case 'T':
        index = T;
        break;
    case 'N':
        index = N;
        break;
    }

    next_node = node->next[index];

    long hits = searchWithMismatches(next_node, query + 1, mismatches_left);

    if (mismatches_left > 0 && !hits)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i != index)
            {
                // hits += searchWithMismatches(node->next[i], query + 1, mismatches_left - 1);
                hits = searchWithMismatches(node->next[i], query + 1, mismatches_left - 1);
            }
        }
    }

    return hits;
}

/*
    Function: buildPrefixTrie
    Purpose: Build a prefix trie from a subject
    Parameters: char* subject - subject to build the trie from
                long long subject_length - length of the subject
                long query_count - number of queries to be generated
    Returns: void
    Time Complexity: O(n) where n is the length of the subject
*/
void Prefix_Trie::buildPrefixTrie(char *subject, long long subject_length, long query_count, int flag_error)
{
    cout << "Building prefix trie..." << endl;
    char *query = new char[36 + 1];

    long nodes = 0;

    for (long long i = 0; i < query_count; i++)
    {
        long long start_index = rand() % (subject_length - 36 + 1);
        for (long long j = 0; j < 36; j++)
        {
            query[j] = subject[start_index + j];
            // query[j] = subject[i + j];
            if(flag_error)
            {
                float error_rate = rand() / static_cast<float>(RAND_MAX);

                int idx;

                if(error_rate <= ERROR_THRESHOLD)
                {
                    char choice = subject[start_index + j];
                    
                    switch(choice)
                    {
                        case 'A': 
                            idx = 0;
                            while(idx == 0)
                                idx = rand() % 5;
                            query[j] = available_chars_in_genome[idx]; 
                            break;
                        case 'C':
                            idx = 1;
                            while(idx == 1)
                                idx = rand() % 5;
                            query[j] = available_chars_in_genome[idx]; 
                            break;
                        case 'G': 
                            idx = 2;
                            while(idx == 2)
                                idx = rand() % 5;
                            query[j] = available_chars_in_genome[idx]; 
                            break;
                        case 'T': 
                            idx = 3;
                            while(idx == 3)
                                idx = rand() % 5;
                            query[j] = available_chars_in_genome[idx]; 
                            break;
                        case 'N': 
                            idx = 4;
                            while(idx == 4)
                                idx = rand() % 5;
                            query[j] = available_chars_in_genome[idx]; 
                            break;
                    }
                }
            }
        }
        query[36] = '\0';

        nodes += insert(query);
    }

    cout << "Prefix trie built" << endl;

    cout << endl << "Total nodes in a prefix trie: " << nodes << endl;

    delete[] query;
}