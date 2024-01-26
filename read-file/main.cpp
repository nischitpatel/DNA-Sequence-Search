/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large Scale Data Structure
    Assignment: 1
*/

// Pre-processors
#include <iostream>
#include <string.h>
#include "genome.h"

using namespace std;

// Main block
int main(int argc, char const *argv[])
{
    //check if proper commands are passed
    if (argc == 4)
    {
        //if command is to asses the content of genome file
        if (strcmp("assess", argv[1]) == 0)
        {
            assess_human_genome(argv[2], argv[3]);
        }

        //if command is to read genome file
        else if (strcmp("read", argv[1]) == 0)
        {
            read_human_genome(argv[2], argv[3]);
        }

        else
        {
            cout << "ERROR: Invalid command" << endl;
        }
    }

    else
    {
        cout << "ERROR: Invalid arguments" << endl;
    }

    return 0;
}
