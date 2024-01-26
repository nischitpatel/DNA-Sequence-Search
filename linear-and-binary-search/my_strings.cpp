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
    while (*query1 && *query2)
    {
        // If *query1 and *query2 are not equal
        if(*query1 != *query2)
        {
            if (*query1 - *query2 > 0)
                return 1;
            
            return -1;
        }

        // Increment to the next character of a string 
        query1++;
        query2++;
    }

    if (*query1) return 1;

    else if (*query2) return -1;

    // If strings are equal then return 0
    return 0;
}
