// Pre-processors
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
//user defined header file
#include "genome.h"

using namespace std;

/*
    Function name: calculate_genome_chars_in_file
    Input parameter: pointer to an input file
    Function: This function will count total number
              of characters in genome data file
*/
long long int calculate_genome_chars_in_file(std::ifstream &ip_file_pointer)
{
    // required variable declaration
    std::string line;
    long long int index;
    long long int line_length;

    // characters counter
    long long int char_count = 0;

    // read file line by line
    while (getline(ip_file_pointer, line))
    {
        if (line[0] != '>')
        {
            line_length = line.length();

            for (index = 0; index < line_length; index++)
            {
                // increment a char_count by 1
                char_count++;
            }
        }
    }

    return char_count;
}

/*
    Function name: read_human_genome
    Input parameter: (std::string) ip_file_path: input file path
                     (std::string) op_file_path: output file path
    Function: This function will count total number scaffolds, and
              Average scaffold length along with the lengths of
              Largest and shortest scaffold and their names
*/
void read_human_genome(std::string ip_file_path, std::string op_file_path)
{

    // variable declaration
    struct Genome genome;

    string line;
    long long int line_length, index;

    // input and output file pointers
    std::ifstream ip_file_pointer;
    std::ofstream op_file_pointer;

    // open input file
    ip_file_pointer.open(ip_file_path);

    // find the number of characters in genome
    long long int size = calculate_genome_chars_in_file(ip_file_pointer);

    // clear the end of file(EOF) character and bring pointer at the start of the file
    ip_file_pointer.clear();
    ip_file_pointer.seekg(0, ios::beg);

    // initialize the character array with the size
    genome.genome_data = new char[size + 1];

    // set the genome size to the variable genome_size in struct Genome
    genome.genome_size = size;

    // open the output file
    op_file_pointer.open(op_file_path);

    // check if file is open or not
    if (ip_file_pointer.is_open())
    {
        // declare and initialize required variables
        long long int scaffold_length = -1,
                      scaffold_count = 0,
                      genome_index = 0,
                      max_scaffold_length = -1,
                      min_scaffold_length = __LONG_LONG_MAX__;

        string min_scaffold_name = "",
               max_scaffold_name = "",
               name;

        // read file line by line
        while (getline(ip_file_pointer, line))
        {
            // check the header line for new scaffold
            if (line[0] == '>')
            {
                scaffold_count++;

                // update max_scaffold_length and max_scaffold_name
                if (max_scaffold_length < scaffold_length)
                {
                    max_scaffold_length = scaffold_length;
                    max_scaffold_name = name;
                }

                // update min_scaffold_length and min_scaffold_name
                if (min_scaffold_length > scaffold_length && scaffold_length != -1)
                {
                    min_scaffold_length = scaffold_length;
                    min_scaffold_name = name;
                }

                // start new scaffold with length 0
                scaffold_length = 0;

                name = line;
            }
            else
            {
                line_length = line.length();
                scaffold_length += line_length;

                // update genome_data array
                for (index = 0; index < line_length; index++)
                {
                    genome.genome_data[genome_index++] = line[index];
                }
            }
        }

        // check for max updation
        if (max_scaffold_length < scaffold_length)
        {
            max_scaffold_length = scaffold_length;
            max_scaffold_name = name;
        }

        // check for min updation
        if (min_scaffold_length > scaffold_length)
        {
            min_scaffold_length = scaffold_length;
            min_scaffold_name = name;
        }

        // write data in output file
        if (op_file_pointer.is_open())
        {
            op_file_pointer << "\tReading Genome Data" << endl;
            op_file_pointer << "------------------------------------" << endl
                            << endl;

            op_file_pointer << "Total number of scaffolds: " << scaffold_count << endl
                            << endl;

            op_file_pointer << "\tLargest Scaffold" << endl;
            op_file_pointer << "-------------------------------------" << endl
                            << endl;
            op_file_pointer << "Name: " << max_scaffold_name << endl;
            op_file_pointer << "Length: " << max_scaffold_length << endl
                            << endl;

            op_file_pointer << "\tSmallest Scaffold" << endl;
            op_file_pointer << "-------------------------------------" << endl
                            << endl;
            op_file_pointer << "Name: " << min_scaffold_name << endl;
            op_file_pointer << "Length: " << min_scaffold_length << endl
                            << endl;

            op_file_pointer << "Average scaffold size: " << genome.genome_size / (double)scaffold_count << endl
                            << endl;

            op_file_pointer << "Length of genome: " << genome.genome_size << endl
                            << endl;
        }

        // close input and output file
        ip_file_pointer.close();
        op_file_pointer.close();
    }
}

/*
    Function name: assess_human_genome
    Input parameter: (std::string) ip_file_path: input file path
                     (std::string) op_file_path: output file path
    Function: This function will count
              The number of A, C, G, T in genome
              Runtime in seconds
              % content of GC in
*/
void assess_human_genome(std::string ip_file_path, std::string op_file_path)
{
    // time variables
    time_t start_time, end_time;

    // store the time in start_time
    time(&start_time);

    // input file pointer
    std::ifstream ip_file_pointer(ip_file_path);
    // output file pointer
    std::ofstream op_file_pointer(op_file_path);

    struct Genome genome;
    long long int line_length, index;
    char genome_char;

    std::string line;

    long long int a_count = 0,
                  g_count = 0,
                  c_count = 0,
                  t_count = 0,
                  other_count = 0,
                  genome_size = 0;

    if (ip_file_pointer.is_open())
    {
        while (getline(ip_file_pointer, line))
        {
            if (line[0] != '>')
            {
                line_length = line.length();

                for (index = 0; index < line_length; index++)
                // for (char genome_char : line)
                {
                    genome_char = line[index];
                    switch (genome_char)
                    {
                    case 'A':
                        a_count++;
                        genome_size++;
                        break;

                    case 'C':
                        c_count++;
                        genome_size++;
                        break;

                    case 'G':
                        g_count++;
                        genome_size++;
                        break;

                    case 'T':
                        t_count++;
                        genome_size++;
                        break;

                    default:
                        other_count++;
                        break;
                    }
                }
            }
        }

        // store the time in end_time
        time(&end_time);

        genome.genome_size = genome_size;

        // store results in output data file
        op_file_pointer << "\tGenome computation" << endl;
        op_file_pointer << "-------------------------------" << endl
                        << endl;

        op_file_pointer << "Total number of characters (A, C, G, T) in genome: " << genome_size << endl
                        << endl;

        op_file_pointer << "Runtime: " << (end_time - start_time) << " seconds" << endl
                        << endl;

        op_file_pointer << "Count of A: " << a_count << endl
                        << endl;
        op_file_pointer << "Count of C: " << c_count << endl
                        << endl;
        op_file_pointer << "Count of G: " << g_count << endl
                        << endl;
        op_file_pointer << "Count of T: " << t_count << endl
                        << endl;

        op_file_pointer << "GC Content: " << (double)((double)(c_count + g_count) / (double)genome_size) * 100 << " %" << endl
                        << endl;

        op_file_pointer << "Count of characters other than A, C, G, T: " << other_count << endl
                        << endl;

        // close input and output files
        ip_file_pointer.close();
        op_file_pointer.close();
    }
}

