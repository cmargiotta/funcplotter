#ifndef _MATH1H_
#define _MATH1H_

#include <stdio.h>
#include "frazioni.h"
#include <math.h>

#define pi 3.141593

int x, y;

int Potenza(int b, int e);
double absol(double b);
double Potenza_double (double b, int esp);
double Radice (double b, int indice);
double Potenza_frazione (double b, frazione esp);
double Rect(double t);
double step(double center, double t, double h);
double Potenza_esponente_double (double b, double esp);
double sinc(double x);
double delta(double x);
double Tri(double base, double x);

double Tri(double base, double x) {
	if (x > -base && x <= 0) {
		return 1 + x/base;	
	}
	if (x < base && x > 0) {
		return 1 - x/base;
	}
	
	return 0;
}

double delta(double x1) {
	double incr = (2*x)/850.0;
	if (x1 < incr && x1 > -incr) {
		return 1;	
	}
	return 0;
}

double sinc(double x) {
	if (x > (-0.001) && x < (0.001)) {
		return 1;	
	}
	double y = sin(pi*x);
	y /= pi*x;
	return y;
}


int Potenza(int b, int esp) {
	switch (esp) {
		case 0: return 1;
		case 1: return b;
		default: return b*Potenza(b, esp-1);
	}
}

double step(double center, double t, double h) {
	if (t >= center) {
		return h;
	}
	else {
		return 0;
	}
}


double Rect(double t) {
	if (t > (-1/2.0) && t < (1/2.0)) {
		return 1.0;
	}
	return 0.0;		
}

int Cifre_decimali(double n) {
	int cifre = 0;
	int n_int = (int) n;
	
	while (n_int != n && cifre <= 6) {
		cifre++;
		n *= 10;
		n_int = (int) n;
	}
	return cifre;
}

double Potenza_double (double b, int esp) {
	switch (esp) {
		case 0: return 1.0;
		case 1: return b;
		default: return b*Potenza_double(b, esp-1);
	}
}

double Logaritmo (double b, double n) {
	if (n == 1 || n < 0) {
		return 0;
	}
	
	double guess = 0.0;
	double pot = Potenza_esponente_double(b, guess);
	
	if (n > b) {
		while (pot < n) {
			guess++;
			pot = Potenza_esponente_double(b, guess);
		}
		
		if (pot > n-0.0001 && pot < n+0.0001) {
			return guess;
		}
		
		guess -= 1.0;
		pot = Potenza_esponente_double(b, guess);
	}
	else {
		while (pot > n) {
			guess--;
			pot = Potenza_esponente_double(b, guess);
		}
		if (pot > n-0.0001 && pot < n+0.0001) {
			return guess;
		}
	}
	
	int cond = 0, d = 0, condi = 1;
	double incr = 0.1;
	
	while (!cond) {
		if (d) {
			d = 0;
			condi = 1; 
			incr /= 10;
			
			if (incr < 0.0000001) {
				return guess;	
			}			
		}
		
		if (b > 1) {
			while (pot < n && condi) {
				if (Potenza_esponente_double(b, guess + incr) > n) {
					d = 1;
					condi = 0;
				}
				else {
					guess += incr;
					pot = Potenza_esponente_double(b, guess);
				}
			}
		}
		else {
			while (pot > n && condi) {
				if (Potenza_esponente_double(b, guess + incr) > n) {
					d = 1;
					condi = 0;
				}
				else {
					guess += incr;
					pot = Potenza_esponente_double(b, guess);
				}
			}
		}
		
		if (pot > n-0.0001 && pot < n+0.0001) {
			return guess;
		}
	}
	
	return 0;
}

double Radice (double b, int indice) {
	if (indice == 1) {
		return b;	
	}
	double guess = 0.0;
	int cond = 0;
	double pot = Potenza_double(guess, indice);

	while (pot < b) {
		guess += 1.0;
		pot = Potenza_double(guess, indice);
	}
	
	if (pot < b + 0.0001 && pot > b - 0.0001) {
		return guess;
	}
	
	guess -= 1.0;
	float incr = 0.1;
	int d = 0, condi = 1;
	pot = Potenza_double(guess, indice);
	while (!cond) {
		if (d) {
			d = 0;
			incr = incr/10.0;
			condi = 1;
			
			if (incr < 0.0000001) {
				return guess;
			}
		}

		while (pot < b && condi) {
			if (Potenza_double(guess + incr, indice) > b) {
				d = 1;
				condi = 0;
			}
			else {
				guess += incr;
				pot = Potenza_double(guess, indice);
			}
		}

		if (pot < b + 0.0001 && pot > b - 0.0001) {
			cond = 1;
		}
	}
	
	return guess;
}

double Potenza_esponente_double (double b, double esp) {
	double old_esp = esp;
	if (esp < 0) {
		esp = abs(esp);
	}
	int cifre = Cifre_decimali(esp);
	frazione esponente;
	if (cifre) {
		esponente = new_frazione((int) (esp*10*cifre), 10*cifre);
	}
	else {
		esponente = new_frazione((int) (esp), 1);
	}
	if (old_esp < 0) {
		return 1/Potenza_frazione (b, esponente);
	}
	
	return Potenza_frazione (b, esponente);
}

double Potenza_frazione (double b, frazione esp) {
	double n = Potenza_double(b, esp.numeratore);
	return(Radice(n, esp.denominatore));
}

double absol(double b) {
	if (b >= 0) {
		return b;
	}
	else {
		return -b;
	}
}

#endif