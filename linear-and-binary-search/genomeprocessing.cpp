/*
    Author: Nischit Bipinbhai Patel
    Course: INF503 Large scale data structures
*/

// Pre-processors
#include "genome_processing.h"

using namespace std;

/*
    Function name: getGenomeSize()
    Input parameter: NONE
    Output parameter (return): genome_size
*/
long long int GENOMEPROCESSING::getGenomeSize()
{
    // Return genome_size
    return genome_size;
}

/*
    Function name: getGenomeData()
    Input parameter: NONE
    Output parameter: *genome_data - pointer to genome data array
*/
char *GENOMEPROCESSING::getGenomeData()
{
    // Return genome_data
    return genome_data;
}

/*
    Function name: setGenomeSize()
    Input parameter: size - size of genome
    Output parameter: NONE
*/
void GENOMEPROCESSING::setGenomeSize(long long int size)
{
    // Set the genome_size to size
    genome_size = size;
}

/*
    Function name: calculateGenomeSize()
    Input parameter: input_file_pointer - pointer to an input file
    Output parameter (return): total genome characters in a file
*/
long long int GENOMEPROCESSING::calculateGenomeSize(ifstream &input_file_pointer)
{
    // Variable declaration
    string line;

    long long int total_genome_chars = 0;

    // Read file
    while (getline(input_file_pointer, line))
    {
        // Check if the line is header line or not
        if (line[0] != HEADER)
        {
            for (auto c : line)
                // Increment total_genome_chars by one
                total_genome_chars++;
        }
    }

    // Return the count of characters in genome file
    return total_genome_chars;
}

/*
    Function name: readHumanGenome()
    Input parameter: input_file_pointer - pointer to an input file
    Output parameter: none
*/
void GENOMEPROCESSING::readHumanGenome(ifstream &input_file_pointer)
{
    // Check if the file is open or not
    if (input_file_pointer.is_open())
    {
        // Variable declaration
        long long int index = 0;

        string line;

        // Calculate size of genome
        long long int size = GENOMEPROCESSING::calculateGenomeSize(input_file_pointer);

        input_file_pointer.clear();

        // Set the file pointer to the begining of a file 
        input_file_pointer.seekg(0, ios::beg);

        // Initialize array to store genome data
        genome_data = new char[size + 1];

        // Set the size of genome
        GENOMEPROCESSING::setGenomeSize(size);

        // Read input file
        while (getline(input_file_pointer, line))
        {
            // Check if the line is header line or not
            if (line[0] != HEADER)
            {
                // Get the characters in line
                for (auto i : line)
                {
                    // Add the character in an array
                    genome_data[index] = i;

                    // Increment an index by one
                    index++;
                }
            }
        }

        cout << "Genome Length : " << genome_size << endl;

        // Close the input file
        input_file_pointer.close();
    }
}

/*
    Function name: assessHumanGenome()
    Input parameter: inutp_file_pointer - pointer to an input file
    Output parameter: none
*/
void GENOMEPROCESSING::assessHumanGenome(ifstream &input_file_pointer)
{
    // Check if an input file is open or not
    if (input_file_pointer.is_open())
    {
        input_file_pointer.clear();

        // Set the file pointer to the beginning of the file
        input_file_pointer.seekg(0, ios::beg);

        // Variable declaration
        string line;

        char genome_char;

        long long int a_count = 0,
                      c_count = 0,
                      g_count = 0,
                      t_count = 0,
                      others_count = 0,
                      genome_size = 0,
                      line_length,
                      curr_genome_size = 0,
                      index;

        time_t start_time, end_time;

        // Get the start time
        time(&start_time);

        // Read input file
        while (getline(input_file_pointer, line))
        {
            // Check if the line is header line or not
            if (line[0] != HEADER)
            {
                // Get the length of a line
                line_length = line.length();

                for (index = 0; index < line_length; index++)
                // for (char genome_char : line)
                {
                    genome_char = line[index];
                    switch (genome_char)
                    {
                    case 'A':
                        a_count++;
                        curr_genome_size++;
                        break;

                    case 'C':
                        c_count++;
                        curr_genome_size++;
                        break;

                    case 'G':
                        g_count++;
                        curr_genome_size++;
                        break;

                    case 'T':
                        t_count++;
                        curr_genome_size++;
                        break;

                    default:
                        others_count++;
                        break;
                    }
                }
            }

            // Get end time
            time(&end_time);

            genome_size = curr_genome_size;

            cout << "\tGenome computation" << endl;
            cout << "-------------------------------" << endl
                 << endl;

            cout << "Total number of characters (A, C, G, T) in genome: " << genome_size << endl
                 << endl;

            cout << "Runtime: " << (end_time - start_time) << " seconds" << endl
                 << endl;

            cout << "Count of A: " << a_count << endl
                 << endl;
            cout << "Count of C: " << c_count << endl
                 << endl;
            cout << "Count of G: " << g_count << endl
                 << endl;
            cout << "Count of T: " << t_count << endl
                 << endl;

            cout << "GC Content: " << (double)((double)(c_count + g_count) / (double)genome_size) * 100 << " %" << endl
                 << endl;

            cout << "Count of characters other than A, C, G, T: " << others_count << endl
                 << endl;

            // Closing the file pointer
            input_file_pointer.close();
        }
    }
}

GENOMEPROCESSING::~GENOMEPROCESSING()
{
    delete[] genome_data;
}
