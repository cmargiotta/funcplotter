#ifndef STRINGUTILSH_
#define STRINGUTILSH_

typedef struct {
	int len;
	char* str;
} string;

/**
*Sets every element of c to '\0'
*@pre c not null
*/
void reset(char *c, int len);

/**
*@ret the length of an array of chars
*@pre c must end with '\0'
*/
int length (char *c);

/**
*generates a string from a char array
*@ret the new string
*/
string new_string (char *s);

/**
*converts a char in the corresponding integer ('1' to 1, etc)
*@ret the corresponding integer, -1 if the char is not numerical
*/
int valueOf_char(char c);

/**
*counts ch in s
*@ret their number
*/
int num_char(string s, char ch);

/**
*@ret the index of the first c in s, -1 if s doesn't contain c
*/
int find_char(string s, char c);

/**
*@ret the double value of a string like "12.5"
*/
double valueOf(string s);

/**
*splits a string in function of c, skipping 'skip' parts:
*string str = new_string("a.b.c");
*string *divided = divide('.', str, 1);
*
*divided[0] will be "a.b" and divided[1] will be "c"
*@ret an array containing the parts
*/
string *divide(char c, string str, int skip);

#endif
