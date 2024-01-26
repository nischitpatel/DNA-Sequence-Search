#ifndef GENOME_H
#define GENOME_H

struct Genome
{
    // array of characters to store genome data
    char *genome_data;

    // variable to store size of genome
    long long int genome_size;
};

long long int calculate_genome_chars_in_file(std::ifstream &ip_file_pointer);
void read_human_genome(std::string ip_file_path, std::string op_file_path);
void assess_human_genome(std::string ip_file_path, std::string op_file_path);

#endif
