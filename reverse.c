/* Reverse-ohjelma 
Tekijä: Marianne Seppänen
Pvm: 11.6.2021
Ohjelma lukee tiedostoa ja tulostaa sen sisällön ruudulle tai toiseen tiedostoon. 
Ohjelman tarkemmat toiminnot riippuvat sille annettujen parametrien määrästä. 
Koodaamisessa on käytetty apuna C-ohjelmoinnin perusteiden ohjelmointiopasta, "C-kieli ja käytännön ohjelmointi, osa 1"
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Tehdään tietue linkitetylle listalle */
struct lista {
char rivi[100];
struct lista *seuraava;
};

int main(int argc, char *argv[]) {
struct lista *pAlku = NULL, *pLoppu = NULL, *ptr;

/* 1 parametri: käyttäjä voi syöttää ohjelmalle tekstiä, joka tulostuu ruudulle. */
if (argc == 1) {
	char text[50];
	fprintf(stdout, "Type something: ");
	fgets(text, 50, stdin);
	fprintf(stdout, "%s\n", text);
}

/* 2 parametriä: ohjelma lukee tiedoston ja tulostaa sen sisällön ruudulle. */
else if (argc == 2) {

	/* Luetaan tiedosto ja lisätään tiedot linkitettyyn listaan */
	char muisti[100];
	FILE *tiedosto;
	if ((tiedosto = fopen(argv[1], "r")) != NULL) {
	while (fgets(muisti, 99, tiedosto) != NULL) {
		/* Muistin varaus */
		if ((ptr = (struct lista*)malloc(sizeof(struct lista)))==NULL) {
			fprintf(stderr, "Malloc failed\n");
			exit(1); }
		strcpy(ptr->rivi, muisti);
		ptr->seuraava = NULL;
		if (pAlku == NULL) { /* Tyhjä lista */
			pAlku = ptr;
			pLoppu = ptr;
		} else { /* Lisätään listan loppuun */
			pLoppu->seuraava = ptr;
			pLoppu = ptr;
		}
	} 
	} else {
		fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
		exit(1); }
	fclose(tiedosto);

	/* Käännetään linkitetty lista ympäri */
	struct lista* edellinen = NULL;
    	struct lista* nyk = pAlku;
    	struct lista* seuraava = NULL;
    	while (nyk != NULL) {
        	seuraava = nyk->seuraava;
        	nyk->seuraava = edellinen;
        	edellinen = nyk;
        	nyk = seuraava;
    		}
    	pAlku = edellinen;

	/* Tulostetaan lista ruudulle */
	ptr = pAlku;
	while (ptr != NULL) {
		fprintf(stdout, "%s", ptr->rivi);
		ptr = ptr->seuraava;
	}
}

/* 3 parametriä:  */
else if (argc == 3) {
	/* Testataan, ovatko input ja output kansiot samoja */
	if (strcmp(argv[1],argv[2]) == 0) {
		fprintf(stderr, "Input and output file must differ.\n");
		exit(1); }
	
	/* Luetaan tiedosto ja lisätään tiedot linkitettyyn listaan */
	char muisti[100];
	FILE *tiedostoIn;
	if ((tiedostoIn = fopen(argv[1], "r")) != NULL) {
	while (fgets(muisti, 99, tiedostoIn) != NULL) {
		/* Muistin varaus */
		if ((ptr = (struct lista*)malloc(sizeof(struct lista)))==NULL) {
			fprintf(stderr, "Malloc failed\n");
			exit(1); }
		strcpy(ptr->rivi, muisti);
		ptr->seuraava = NULL;
		if (pAlku == NULL) { /* Tyhjä lista */
			pAlku = ptr;
			pLoppu = ptr;
		} else { /* Lisätään listan loppuun */
			pLoppu->seuraava = ptr;
			pLoppu = ptr;
		}
	} 
	} else {
		fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
		exit(1); }
	fclose(tiedostoIn);

	/* Käännetään linkitetty lista ympäri, eli lopusta alkuun 
	Listan käännökseen on saatu apua Geeks for geeks -sivustolta
	https://www.geeksforgeeks.org/reverse-a-linked-list/ */
	struct lista* edellinen = NULL;
    	struct lista* nyk = pAlku;
    	struct lista* seuraava = NULL;
    	while (nyk != NULL) {
        	seuraava = nyk->seuraava;
        	nyk->seuraava = edellinen;
        	edellinen = nyk;
        	nyk = seuraava;
    		}
    	pAlku = edellinen;
	
	/* Tallennetaan lista output-tiedostoon */
	FILE *tiedostoOut;
	if ((tiedostoOut = fopen(argv[2], "w")) != NULL) {

	ptr = pAlku;
	while (ptr != NULL) {
		fprintf(tiedostoOut, "%s", ptr->rivi);
		ptr = ptr->seuraava;
	}
	} else {
		fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
		exit(1); }

	fclose(tiedostoOut);

}

/* Yli 3 parametriä: ohjelma tulostaa käyttöohjeen ja lopettaa */
else {
	fprintf(stderr, "usage: reverse <input> <output> \n");
	exit(1);
}

return(0);
}

