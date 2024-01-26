/*
    Author: Nischit Bipinbhai Patel
    NAU ID#: 6293990
    Course: INF503 Large Scale Data Structures
*/

// Pre-processors
#include "Queries_BL.h"
#include "my_strings.h"
// #include "queries_ht.h"
#include <math.h>
#include <time.h>

using namespace std;

// Constructor
Queries_BL::Queries_BL()
{
    hash_table = new LinkedList[HT_SIZE];

    nmer = 16;

    gap=-1;

    match=2;

    mismatch=-1; 
}

Queries_BL::~Queries_BL()
{
    srand(time(NULL));
    // Delete linked list at each index
    Node *temp;

    for (int i = 0; i < HT_SIZE; i++)
    {
        temp = hash_table[i].head;

        while (hash_table[i].head != nullptr)
        {
            temp = hash_table[i].head;

            hash_table[i].head = hash_table[i].head->next;

            delete temp;
        }
    }

    // Delete array
    delete[] hash_table;
}

long long Queries_BL::getRadixValue(char *query)
{
    // Set the radix_value to 0
    long long radix_value = 0;

    // Set the base to 5 as we have 5 characters in our universe
    // { A, C, G, T, N }
    long long base = 5;

    int index = 0;

    // Get the character from the fragment and add digit
    while (index < SEED_SIZE)
    {
        char c = query[index];

        long long int_representation;

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
        default:
            int_representation = 4;
            break;
        }

        // Update radix_value variable
        long long power = pow(base, (SEED_SIZE) - index - 1);

        radix_value += int_representation * power; // pow(base, (FRAGMENT_LENGTH / 2) - index - 1);

        index++;
    }

    // Return the radix value
    return radix_value % HT_SIZE;
}

void Queries_BL::insertInHashTable(char *query, long long index_in_query_dataset)
{
    // Get radix value
    long long index = getRadixValue(query);

    // Create a new node
    Node *new_node = new Node;

    // Copy the query in the fragment
    strcpy(new_node->fragment, query);

    new_node->index = index_in_query_dataset;

    // Set the next pointer to null
    new_node->next = nullptr;

    // If head is null
    if (hash_table[index].head == nullptr)
        hash_table[index].head = new_node;
    else
    {
        new_node->next = hash_table[index].head;
        hash_table[index].head = new_node;
    }
}

void Queries_BL::getQueryDatasetInHashTable(char **query_dataset, long long size_of_query_dataset)
{
    for(long long i=0; i<size_of_query_dataset; i++)
    {
        char seed[SEED_SIZE+1];

        for(int j=0; j<FRAGMENT_LENGTH-SEED_SIZE+1; j++)
        {
            // Copy the seed
            for(int k=j; k<SEED_SIZE+j; k++)
                seed[k-j] = query_dataset[i][k];

            // Set the last character to null
            seed[SEED_SIZE] = '\0';

            // Insert in hash table
            insertInHashTable(seed, i);
        }
    }

    cout << "Hash table created" << endl;

    // for(long long i=0; i<HT_SIZE; i++)
    // {
    //     Node *temp = hash_table[i].head;

    //     while(temp != nullptr)
    //     {
    //         cout << temp->fragment << " " << temp->index << " " ;

    //         temp = temp->next;
    //     }

    //     cout << endl;
    // }
}

int Queries_BL::needlemanWunsch(char *query_fragment, char *fragment)
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

char *Queries_BL::search(char **query_dataset, char *query)
{
    char *seed = new char[SEED_SIZE+1];

    int best_score = 0;

    long long index_in_query_dataset = -1;

    for(int i=0; i<FRAGMENT_LENGTH-SEED_SIZE+1; i++)
    {
        // Copy the seed
        for(int j=i; j<SEED_SIZE+i; j++)
            seed[j-i] = query[j];

        // Set the last character to null
        seed[SEED_SIZE] = '\0';

        // Get radix value
        long long index = getRadixValue(seed);

        // Search in hash table
        Node *temp = hash_table[index].head;

        while(temp != nullptr)
        {
            if(!strCmp(temp->fragment, seed))
            {
               // Pass query and fragment @ temp->index to nw 
               int similarity_score = needlemanWunsch(query, query_dataset[temp->index]);

               if(similarity_score > best_score && similarity_score >= 26)
               {
                   best_score = similarity_score;

                   index_in_query_dataset = temp->index;
               }    

               if(best_score == 32)
                    break;  
            }

            temp = temp->next;
        }

        if(best_score == 32)
            break;
    }

    delete[] seed;

    return index_in_query_dataset==-1 ? NULL : query_dataset[index_in_query_dataset];
}