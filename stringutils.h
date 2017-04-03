#include <stdio.h>
#include "math1.h"

typedef struct stringa {
	int len;
	char* str;
} stringa;

stringa *dividi(char c, stringa s, int skip);
stringa new_string (char *s);
char *literaltoarray(char *c);
int length(char *c);
int num_char(stringa s, char ch);
int valueOf_char(char c);
double valueOf(stringa s);
int find_char(stringa s, char c);

double valueOf(stringa s) {
	int p = num_char(s, '.');
	int i;
	double val = 0;
	
	if (p == 1) {
		int punto = find_char(s, '.');
		
		for (i = 0; i < punto; i++) {
			val += Potenza(10,punto-i-1)*valueOf_char(s.str[i]);	
		}
		
		for (i = punto+1; i < s.len; i++) {
			val += Potenza_double(0.1,i-punto)*valueOf_char(s.str[i]);		
		}
		return val;
	}
	
	for (i = 0; i < s.len; i++) {
		val += Potenza(10,s.len-i-1)*valueOf_char(s.str[i]);
	}
	
	return val;
}

int find_char(stringa s, char c) {
	int i;
	
	for (i = 0; i < s.len; i++) {
		if (s.str[i] == c) {
			return i;	
		}
	}
	
	return -1;
}

int valueOf_char(char c) {
	switch(c) {
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		default: return 0;
	}
}

int num_char(stringa s, char ch) {
	int n = 0;
	int c = 0;
	
	while (c < s.len) {
		if (s.str[c] == ch) {
			n++;	
		}
		c++;
	}
	
	return n;
}

stringa *dividi(char c, stringa string, int skip) {
	char** s = (char **) malloc(2*sizeof(char*));
	int i, found = 0, d = 0;
	
	s[0] = (char*) malloc(string.len*sizeof(char));
	s[1] = (char*) malloc(string.len*sizeof(char));
	for (i = 0; i < string.len; i++) {
		if (string.str[i] == c && !found) {
			if (skip > 1) {
				skip--;
				s[0][i] = string.str[i];
			}
			else {
				found = 1;
				s[0][i] = '\0';
			}
		}
		else {
			if (found) {
				s[1][d] = string.str[i];
				d++;
			}
			else {
				s[0][i] = string.str[i];
			}
		}
	}
	s[1][d] = '\0';
	
	stringa *result = (stringa *) malloc(2*sizeof(stringa));
	result[0] = new_string(s[0]); 
	result[1] = new_string(s[1]);
	return result;
}

int length (char *c) {
	int len = 0;
	
	while (c[len] != '\0') {
		len++;	
	}
	
	return len;
}

stringa new_string (char *s) {
	stringa string = {length(s), s};
	return string;
}

char *literaltoarray(char *c) {
	int len = length(c), i;
	char *s = (char *) malloc(len * sizeof(char));
	
	for (i = 0; i < len; i++) {
		s[i] = c[i];	
	}
	
	return s;
}