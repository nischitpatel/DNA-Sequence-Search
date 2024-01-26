/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large Scale Data Structures
    NAU ID #: 6293990
*/

#ifndef PREFIX_TRIE_H
#define PREFIX_TRIE_H

// char AVAILABLE_CHARS_IN_GENOME[] = {'A', 'C', 'G', 'T', 'N'};

#define A 0
#define C 1
#define G 2
#define T 3
#define N 4

#define ERROR_THRESHOLD 0.05
#define ALLOWED_MISMATCHES 1

// Structure of a node in the trie
struct Node
{
    Node *next[5]; // [A, C, G, T, N]
    // long query_occured = 0;

    Node()
    {
        for(int i = 0; i < 5; i++)
        {
            next[i] = nullptr;
        }
    }
    // ~Node()
    // {
    //     for(int i = 0; i < 5; i++)
    //     {
    //         if(next[i] != nullptr)
    //         {
    //             delete next[i];
    //         }
    //     }
    // }
};

class Prefix_Trie
{
private:
    Node *root;
    char available_chars_in_genome[5] = {'A', 'C', 'G', 'T', 'N'};
    long searchWithMismatches(Node *node, char *query, int mismatches_left);

public:
    Prefix_Trie();
    Prefix_Trie(char *subject, long long subject_length, long query_count, int flag_error);
    Prefix_Trie(const Prefix_Trie& clone_object);
    ~Prefix_Trie();
    void deleteTrie(Node *node);
    Node *copyTrie(Node *node);
    long insert(char *query);
    long search(char *query);
    void buildPrefixTrie(char *subject, long long subject_length, long query_count, int flag_error);
};

#endif // "PREFIX_TRIE_H"