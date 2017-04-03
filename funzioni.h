#include <stdio.h>
#include "stringutils.h"
#include <math.h>
#include <stdlib.h>
#include "math1.h"

#define pi 3.141593
#define e 2.718282

typedef struct elemento {
	/*  
	1. Somma
	2. Prodotto
	3. Sottrazione
	4. Divisione
	5. Potenza
	6. Logaritmo naturale
	7. Seno
	8. Coseno
	9. Radice quadrata
	a. Costante
	b. Sinc
	c. x
	d. Rect
	e. Delta
	f. Abs
	g. Tri
	h. Parametro
	*/
	
	char tipo;
	double valore;
	struct elemento* argomento;
	struct elemento* prec;
	int animata;
} elemento;

typedef elemento* funzione;

double Calcola(funzione f, double x, double p);
funzione new_funzione(stringa s);
int Memoria_occupata(stringa s);
int Verifica_Parentesi(stringa s);
stringa Pulisci(stringa s);
stringa Rimuovi_parentesi(stringa s);
funzione argom(stringa s, int i);
double area(double i, double y1, double y2);
double distanza(double x1, double x2, double y1, double y2);
stringa aggiungipar(stringa s);
double areatot(double *punti1, double *punti2, double incr);

double distanza(double x1, double x2, double y1, double y2) {
	double distanza = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
	return distanza;
}

double area(double incr, double y1, double y2) {
	double area;
	if ((y1 > -incr && y1 < incr) || (y2 > -incr && y2 < incr)) {
		return 0;	
	}
	if (y1 <= y2) {
		area = incr*y1;
		if (absol(y2) > absol(y1)+0.001) {
			area += incr*(y2-y1)/2;
		}
	}
	else {
		area = incr*y2;
		if (absol(y1) > absol(y2)+0.001) {
			area += incr*(y1-y2)/2;
		}
	}
	
	return area;
}

double areatot(double *punti1, double *punti2, double incr) {
	int i;
	double areatratto;
	double a = 0;
	double k = 644.0/(2*y);
	
	for (i = 1; i < 840; i++) {
		areatratto = k*area(incr, punti1[i-1]/k, punti1[i]/k);
		areatratto *= k*area(incr, punti2[i-1]/k, punti2[i]/k);
		a += areatratto;
	}
	
	return a;
}

stringa aggiungipar(stringa s) {
	int x = num_char(s, 'x');
	int a = num_char(s, 'a');
	if (a < x) {
		int len = s.len + x*5;
		char *c = (char *) malloc(len+1);
		int d=0, i;
		for (i = 0; i < s.len; i++) {
			if (s.str[i] == 'x') {
				c[d] = '(';
				d++;
				c[d] = '-';
				d++;
				c[d] = s.str[i];
				d++;
				c[d] = '+';
				d++;
				c[d] = 'a';
				d++;
				c[d] = ')';
				d++;
			}
			else {
				c[d] = s.str[i];
				d++;	
			}
		}
		c[d] = '\0';
		stringa result = {len, c};
		return result;
	}
	
	return s;
}

stringa Rimuovi_parentesi(stringa s) {
	if (s.str[0] == '(' && s.str[s.len-1] == ')') {
		char *c = (char *) malloc(s.len-1);
		int i, j=0;
		for (i = 1; i < s.len-1; i++) {
			c[j] = s.str[i];
			j++;
		}
		c[j] = '\0';
		stringa pulita = new_string(c);
		if (Verifica_Parentesi(pulita)) {
			return pulita;	
		}
		free(c);
	}
	return s;
}

stringa Pulisci(stringa s) {
	int i = num_char(s, ' '), j = 0;
	char *c;
	if (s.str[0] == '-') {
		j++;
		c = (char *) malloc(s.len-i+2);
		c[0] = '0';
		for (i = 1; i < s.len+1; i++) {
			if (s.str[i-1] != ' ') {
				c[j] = s.str[i-1];
				j++;
			}
		}
	}
	else {
		c = (char *) malloc(s.len-i+1);
		for (i = 0; i < s.len; i++) {
			if (s.str[i] != ' ') {
				c[j] = s.str[i];
				j++;
			}
		}
	}
	c[j] = '\0';
	stringa str = new_string(c);
	str = Rimuovi_parentesi(str);
	return str;
}

int Memoria_occupata(stringa s) {
	int m = 1;
	m += num_char(s, '+');
	m += num_char(s, '-');
	m += num_char(s, '*');
	m += num_char(s, '/');
	m += num_char(s, 's');
	m += num_char(s, 'l');
	m += num_char(s, '^');
	m += num_char(s, 'x');
	
	m *= 21;
	
	return m;
}

int Verifica_Parentesi(stringa s) {
	int control = 0, i;
	
	for (i = 0; i < s.len; i++) {
		if (s.str[i] == '(') {
			control++;	
		}
		if (s.str[i] == ')') {
			if (control > 0) {
				control--;	
			}
			else {
				return 0;	
			}
		}
	}
	
	if (control == 0) {
		return 1;	
	}
	return 0;
}

funzione argom(stringa s, int i) {
	stringa *parti;
	parti = dividi(',', s, 0);
	
	return new_funzione(parti[i]);
}

funzione new_funzione(stringa s) {
	s = Pulisci(s);
	funzione f = (elemento *) malloc(sizeof(elemento));
	stringa *parti;
	int i, j;
	int num;
	char c[5] = {'+','*','-','/','^'};
	char t[5] = {'1','2','3','4','5'};
	
	for (i = 0; i < 5; i++) {
		num = num_char(s, c[i]);
		j = 1;
		if (num >= 1) {
			if (i == 2) {
				parti = dividi(c[i], s, num);
				while (!(parti[1].len > 0 && Verifica_Parentesi(parti[0])) && j > 0) {
					j--;
					parti = dividi(c[i], s, j);
				}
			}
			else {
				parti = dividi(c[i], s, 1);
				while (!(parti[1].len > 0 && Verifica_Parentesi(parti[0])) && j <= num) {
					j++;
					parti = dividi(c[i], s, j);
				}
			}
			if (parti[1].len > 0 && Verifica_Parentesi(parti[0])) {
				f->tipo = t[i];
				f->prec = new_funzione(parti[0]);
				f->argomento = new_funzione(parti[1]);
				if (num_char(s,'a') > 0) {
					f->animata = 1;	
				}
				else {
					f->animata = 0;
				}
				return f;
			}
		}
	}
	
	if (s.str[0] == 'a' && s.len == 1) {
		f->tipo = 'h';
		f->animata = 1;
		return f;
	}
	
	char c1[5] = {'l','c','r','a','d'};
	char id[5] = {'6','8','d','f','e'};
	int l[5] = {4,4,5,4,6};
	
	for (i = 0; i < 6; i++) {
		if (s.str[0] == c1[i]) {
			char *argomento = (char *) malloc(s.len-l[i]);
			for (j = 0; j < s.len-l[i]; j++) {
				argomento[j] = s.str[j+l[i]];	
				if (j == s.len-l[i]-1) {
					argomento[j] = '\0';
				}
			}
			stringa arg = {s.len-l[i], argomento};
			f->tipo = id[i];
			f->argomento = new_funzione(arg);
			if (num_char(s,'a') > 0) {
				f->animata = 1;	
			}
			else {
				f->animata = 0;
			}
			return f;
		}
	}
	
	if (s.str[0] == 't') {
		char *argomento = (char *) malloc(s.len-4);
		for (i = 0; i <= s.len-5; i++) {
			argomento[i] = s.str[i+4];	
			if (i == s.len-5) {
				argomento[i] = '\0';	
			}
		}
		stringa arg = {s.len-4, argomento};
		f->tipo = 'g';
		f->valore = argom(arg,0)->valore;
		f->argomento = argom(arg,1);
		if (num_char(s,'a') > 0) {
			f->animata = 1;	
		}
		else {
			f->animata = 0;
		}
		return f;
	}
	
	if (s.str[0] == 's') {
		if (s.str[1] == 'i') {
			if (s.str[3] == 'c') {
				char *argomento = (char *) malloc(s.len-5);
				for (i = 0; i <= s.len-6; i++) {
					argomento[i] = s.str[i+5];	
					if (i == s.len-6) {
						argomento[i] = '\0';	
					}
				}
				stringa arg = {s.len-5, argomento};
				f->tipo = 'b';
				f->argomento = new_funzione(arg);
				if (num_char(s,'a') > 0) {
					f->animata = 1;	
				}
				else {
					f->animata = 0;
				}
				return f;
			}
			char *argomento = (char *) malloc(s.len-4);
			for (i = 0; i <= s.len-5; i++) {
				argomento[i] = s.str[i+4];	
				if (i == s.len-5) {
					argomento[i] = '\0';	
				}
			}
			stringa arg = {s.len-4, argomento};
			f->tipo = '7';
			f->argomento = new_funzione(arg);
			if (num_char(s,'a') > 0) {
				f->animata = 1;	
			}
			else {
				f->animata = 0;
			}
			return f;
		}
		else {
			char *argomento = (char *) malloc(s.len-5);
			for (i = 0; i <= s.len-6; i++) {
				argomento[i] = s.str[i+5];	
				if (i == s.len-6) {
					argomento[i] = '\0';	
				}
			}
			stringa arg = {s.len-5, argomento};
			f->tipo = '9';
			f->argomento = new_funzione(arg);
			if (num_char(s,'a') > 0) {
				f->animata = 1;	
			}
			else {
				f->animata = 0;
			}
			return f;
		}
	}
	
	if (s.str[0] == 'x') {
		f->tipo = 'c';
		f->animata = 0;
		return f;
	}
	
	f->tipo = 'a';
	if (s.str[0] == 'e') {
		f->valore = e;	
	}
	else {
		f->valore = valueOf(s);
	}
	f->animata = 0;
	return f;
}

double Calcola(funzione f, double x, double parametro) {
	switch (f->tipo) {
		case '1': //Somma
			return (Calcola(f->prec, x, parametro)+Calcola(f->argomento, x, parametro));	
		case '2': //Prodotto
			return (Calcola(f->prec, x, parametro)*Calcola(f->argomento, x, parametro));	
		case '3': //Sottrazione
			return (Calcola(f->prec, x, parametro)-Calcola(f->argomento, x, parametro));	
		case '4': //Divisione
			return (Calcola(f->prec, x, parametro)/Calcola(f->argomento, x, parametro));
		case '5': //Potenza
			return pow(Calcola(f->prec, x, parametro), Calcola(f->argomento, x, parametro));
		case '6': //Logaritmo naturale
			return log(Calcola(f->argomento, x, parametro));
		case '7': //Seno
			return sin(Calcola(f->argomento, x, parametro));
		case '8': //Coseno
			return cos(Calcola(f->argomento, x, parametro));
		case '9': //Radice quadrata
			return sqrt(Calcola(f->argomento, x, parametro));
		case 'a': //Costante
			return f->valore;
		case 'b': //Sinc
			return sinc(Calcola(f->argomento, x, parametro));
		case 'c': //x
			return x;
		case 'd': //Rect
			return Rect(Calcola(f->argomento, x, parametro));
		case 'e': //Delta
			return delta(Calcola(f->argomento, x, parametro));
		case 'f': //Abs
			return absol(Calcola(f->argomento, x, parametro));
		case 'g': //Tri
			return Tri(f->valore, Calcola(f->argomento, x, parametro));
		case 'h': //Parametro
			return parametro;
		default: return 0;
	}
}