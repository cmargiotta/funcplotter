#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math1.h"
#include "stringutils.h"

void reset(char *c, int len) {
	int i;

	for (i = 0; i < len; i++) {
		c[i] = '\0';
	}
}

int length (char *c) {
	int len = 0;

	while (c[len] != '\0') {
		len++;
	}

	return len;
}

string new_string (char *s) {
	string string = {length(s), s};
	return string;
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
		case '0': return 0;
		default: return -1;
	}
}

int num_char(string s, char ch) {
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

int find_char(string s, char c) {
	int i;

	for (i = 0; i < s.len; i++) {
		if (s.str[i] == c) {
			return i;
		}
	}

	return -1;
}

double valueOf(string s) {
	int p = num_char(s, '.');
	int i;
	double val = 0;

	if (p == 1) {
		int point = find_char(s, '.');

		for (i = 0; i < point; i++) {
			val += pow(10,point-i-1)*valueOf_char(s.str[i]);
		}

		for (i = point+1; i < s.len; i++) {
			val += pow(0.1,i-point)*valueOf_char(s.str[i]);
		}
		return val;
	}

	for (i = 0; i < s.len; i++) {
		val += pow(10,s.len-i-1)*valueOf_char(s.str[i]);
	}

	return val;
}

string *divide(char c, string str, int skip) {
	char** s = (char **) malloc(2*sizeof(char*));
	int i, found = 0, d = 0;

	s[0] = (char*) malloc(str.len*sizeof(char));
	s[1] = (char*) malloc(str.len*sizeof(char));
	for (i = 0; i < str.len; i++) {
		if (str.str[i] == c && !found) {
			if (skip > 1) {
				skip--;
				s[0][i] = str.str[i];
			}
			else {
				found = 1;
				s[0][i] = '\0';
			}
		}
		else {
			if (found) {
				s[1][d] = str.str[i];
				d++;
			}
			else {
				s[0][i] = str.str[i];
			}
		}
	}
	s[1][d] = '\0';

	string *result = (string *) malloc(2*sizeof(string));
	result[0] = new_string(s[0]);
	result[1] = new_string(s[1]);

	return result;
}
