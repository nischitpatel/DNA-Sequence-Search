# DNA Sequence Search

## Description:
This GitHub repository showcases an in-depth exploration of handling large-scale data structures with a progressive approach to optimization. Here we are searching DNA sequences from 3 Biliion sequences. The journey begins with a basic brute-force implementation, emphasizing simplicity in processing and searching through extensive datasets. As the scale of data grows, it becomes evident that the brute-force approach is impractical due to excessive processing times.

The repository provides a comprehensive demonstration of transitioning from the brute-force methodology to more efficient data structures. The initial implementation focuses on the challenges posed by large-scale data and highlights the need for optimization. Subsequent iterations introduce advanced data structures such as hash tables, illustrating their effectiveness in enhancing search efficiency.

As the optimization journey continues, the repository culminates in the implementation of a prefix trie. This powerful data structure proves to be a game-changer in terms of both processing speed and memory utilization, making it an ideal solution for handling vast amounts of data.

## Key Features:
1. Brute Force Implementation: Understand the challenges of large-scale data processing with a simple brute-force approach.
2. Hash Tables: Explore the benefits of hash tables for efficient data searching and retrieval.
3. Prefix Trie: Witness the transformational impact of implementing a prefix trie for optimized data structure handling.

## helpers
It contains user defined helper functions such as strCmp to compare 2 strings. And functions to read file and get the data from the file.

## read-file
This is to know the contents in the file. To get familiar with the data stored in file.

## linear-and-binary-search
In this, I have tried searching queries using linear search(brute-force) and binary search to analyse the time required for searching queries.

## hash-table
In this, I have used hash table to store queries and make search process faster. To handle the collisions, I have used linked list.

## sequence-alignment-algorithms
### Needleman-Wunsch algorith (Gloabal alignment algorithm)
1. Initialization: Create a matrix to store alignment scores, and initialize the first row and column with gap penalties.
2. Score Calculation: Calculate alignment scores for each cell in the matrix based on match/mismatch and gap penalties.
3. Traceback: Trace back through the matrix to determine the optimal alignment.

### BLAST algorithm (Basic Local Alignment Search Tool)
The basic steps of the BLAST algorithm are as follows:

1. Seed Finding: Identify short, exact matches (seeds) between the query sequence and sequences in the database.
2. Extension: Extend the seed matches in both directions to form local alignments.
3. Scoring: Assign scores to the local alignments based on matches, mismatches, and gaps.
4. Filtering: Apply statistical filters to eliminate low-scoring matches.
5. Reporting: Present the significant local alignments as results.

## prefix-trie
In this, I have used prefix trie to store queries. Searching in a prefix trie is significantly faster than all the previous techniques.
