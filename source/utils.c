/**
 Project:	lightshell

 file: 	utils.c
 By: 	NightLamp

**/


#include "lightshell.h"



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
char *getSubstring(char *str, int start, int end) {
	
	int ogLength = strlen(str);
	if (start > end) {

		fprintf(stderr, "getSubstring: Start bound higher than end bound\n");
		return NULL; 
	}	
	else if (end > ogLength) {

		fprintf(stderr, "getSubstring: End bound excedes string\n");
		return NULL;
	}
	char *substr = malloc( sizeof(char) * (end - start + 1) );
	// i indexes string, k indexes substring
	for (int i = start, k = 0; i < end; i++, k++) {
		substr[k] = str[i];
	}
	substr[end - start + 1] = '\0';
	return substr;
}
