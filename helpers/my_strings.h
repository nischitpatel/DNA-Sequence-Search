#ifndef MY_STRINGS_H
#define MY_STRINGS_H

using namespace std;

/*
    Function name: strCmp()
    Input data: *query1 - string to compare
                *query2 - string to compare
    Output data (return): 0 - if both strings are equal
                          1 - if *query1 > *query2
                         -1 - if *query1 < *query2
*/
int strCmp(char *query1, char *query2);

/*
    Function name: strCpy()
    Input data: *dest - string in which we have to copy another string
                *query2 - string that will be copied to dest 
    Output data (return): dest - 
*/
char* strCpy(char *dest, char *src);

#endif
