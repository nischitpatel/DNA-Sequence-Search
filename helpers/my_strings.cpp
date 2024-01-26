#include "my_strings.h"

/*
    Function name: strCmp()
    Input data: *query1 - string to compare
                *query2 - string to compare
    Output data (return): 0 - if both strings are equal
                          1 - if *query1 > *query2
                         -1 - if *query1 < *query2
*/
int strCmp(char *query1, char *query2)
{
    while (*query1!='\0' && *query2!='\0')
    {
        // If *query1 and *query2 are not equal
        if (*query1 != *query2)
        {
            return 1;
        }

        // Increment to the next character of a string
        query1++;
        query2++;
    }
    // If strings are equal then return 0
    return 0;
}

/*
    Function name: strCpy()
    Input data: *dest - string in which we have to copy another string
                *query2 - string that will be copied to dest
    Output data (return): dest -
*/
char *strCpy(char *dest, char *src)
{
    int i = 0;

    // Copy src to dest
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0'; // Null-terminate the destination string

    return dest; // Return dest
}
