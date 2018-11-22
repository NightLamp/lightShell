//my Utility functions I use reqularly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** 
 * Gets a substring from within a given string, between start and upto (but not including)
 * end bound. Requires string.h to be included. returned string should be freed after use as
 * malloc is used to store the string.
 *
 * @param	str		original string
 * @param	start	int for start index (includes char at this index)
 * @param	end		int for end index (doesn't include char at this index  
 * 
 * @return			substring between start and end bounds. The returned string should
 *                  be freed after use. 
 */
char *getSubstring(char *str, int start, int end) 
{	
	int ogLength = strlen(str);
	if (start > end) 
	{
		fprintf(stderr, "getSubstring: Start bound higher than end bound\n");
		return NULL; 
	}	
	else if (end > ogLength) 
	{
		fprintf(stderr, "getSubstring: End bound excedes string\n");
		return NULL;
	}
	char *substr = malloc( sizeof(char) * (end - start + 1) );
	// i indexes string, k indexes substring
	for (int i = start, k = 0; i < end; i++, k++) 
	{
		substr[k] = str[i];
	}
	substr[end - start + 1] = '\0';
	return substr;
}


/**
 * Returns 1 if the value is between the bounds given (inclusively).
 *
 * @param	val		value to check
 * @param 	b1		the first bound
 * @param	b2		the second bound
 * 
 * @return 	int		1 if val is in between b1 and b2,
 *					0 if not in bounds b1 and b2,
 */
int inBounds(int val, int b1, int b2) 
{
	//find uppper and lower bounds
	int bu = b1, bd = b2;
	if (b1 < b2)
	{
		bu = b2; bd = b1;
	}

	if ( val <= bu && val >= bd ) return 1;
	else return 0;
}



/**
 * Changes a string to all lowercase, modifies the string in doing so.
 *
 * @param	str		the string
 *
 * @return 	int		an integer indicating the success or failure of function.
 */
int strLower(char *str) 
{
	int i = 0;
	char c;
	while ( (c = str[i]) != '\0' ) 
	{
		if ( inBounds(c, 'A', 'Z') ) 
		{
			str[i] = c + 'a' - 'A';		//adds difference between upper and lower to convert
		}
		
		i++;
	}
	return 0;
}



