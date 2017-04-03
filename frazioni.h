#include <stdio.h>

typedef struct frazione{
	int numeratore, denominatore;
} frazione;

frazione new_frazione(int n, int d);
frazione Somma(frazione n, frazione d);
frazione Prodotto(frazione f1, frazione f2);
frazione Differenza(frazione f1, frazione f2);
frazione FloatToFraz(float n);

frazione new_frazione(int numeratore, int denominatore) {
	int mcd = 2;
	if (numeratore != 0) {
		if (numeratore%denominatore == 0) {
			numeratore = numeratore/denominatore;
			denominatore = 1;
		}
		else {		
			if (denominatore%numeratore == 0) {
				denominatore = denominatore/numeratore;
				numeratore = 1;			
			}
			else {
				int cond = 1;

				while (cond) {
					if ((numeratore%mcd == 0) && (denominatore%mcd == 0)) {
						numeratore = numeratore/mcd;
						denominatore = denominatore/mcd;
						mcd = 1;
					}

					mcd++;

					if ((mcd > denominatore/2) || (mcd > numeratore/2)) {
						cond = 0;
					}
				}
			}
		}
	}
	
	frazione fraz = {numeratore, denominatore};
	return fraz;
}

frazione FloatToFraz(float n) {
	int n_int = (int) n;
	int c = 0;
	
	while (n_int != n) {
		n = n*10;
		n_int = (int) n;
		c++;
	}
	
	frazione result;
	if (c == 0) {
		result = new_frazione((int) n, 1);		
	}
	else {
		result = new_frazione(n, 10*c);	
	}
	
	return result;
}

frazione Somma(frazione fraz1, frazione fraz2) {
	int mcm = fraz1.denominatore * fraz2.denominatore;
	int numeratore = (fraz1.numeratore*fraz2.denominatore) + (fraz2.numeratore*fraz1.denominatore);
	
	frazione somma = new_frazione(numeratore, mcm);
	
	return somma;
}

frazione Differenza(frazione fraz1, frazione fraz2) {
	int mcm = fraz1.denominatore * fraz2.denominatore;
	int numeratore = (fraz1.numeratore*fraz2.denominatore) - (fraz2.numeratore*fraz1.denominatore);
	
	frazione diff = new_frazione(numeratore, mcm);
	
	return diff;
}


frazione Prodotto(frazione fraz1, frazione fraz2) {
	frazione prodotto = new_frazione((fraz1.numeratore*fraz2.numeratore), (fraz1.denominatore*fraz2.denominatore));
	
	return prodotto;
}



