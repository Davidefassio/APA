#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXL 255

typedef struct{
	int nr;        // Numero di righe
	int *nc;       // Numero di colonne per riga
	char ***brani; // Matrice di stringhe
}Item;

Item leggiBrani(FILE *f){
	Item it;
	int i, j;

	fscanf(f, "%d", &it.nr);
	it.nc = (int*) malloc(it.nr * sizeof(int));
	it.brani = (char***) malloc(it.nr * sizeof(char**));
	for(i = 0; i < it.nr; ++i){
		fscanf(f, "%d", &it.nc[i]);
		it.brani[i] = (char**) malloc(it.nc[i] * sizeof(char*));
		for(j = 0; j < it.nc[i]; ++j){
			it.brani[i][j] = (char*) malloc(MAXL * sizeof(char));
			fscanf(f, "%s", it.brani[i][j]);
		}
	}
	return it;
}

// Funzione ricorsiva
void stampaCombinazioniR(Item *it, int r, char *str){
	int i;
	if(r == it->nr - 1){
		for(i = 0; i < it->nc[r]; ++i)
			printf("%s %s\n", str, it->brani[r][i]);
		return;
	}

	char *m;
	for(i = 0; i < it->nc[r]; ++i){
		m = (char*) malloc(it->nr * MAXL * sizeof(char));

		strcpy(m, str);
		strcat(m, " ");
		strcat(m, it->brani[r][i]);

		stampaCombinazioniR(it, r+1, m);
		free(m);
	}
}

// Wrapper
void stampaCombinazioni(Item it){
	char *str = (char*) malloc(it.nr * MAXL * sizeof(char));
	str[0] = '\0';
	stampaCombinazioniR(&it, 0, str);
	free(str);
}

int main(int argc, char *argv[]){
	FILE *fp = fopen("brani.txt", "r");
	if(fp == NULL) exit(EXIT_FAILURE);

	Item it;

	it = leggiBrani(fp);
	fclose(fp);
	
	stampaCombinazioni(it);
	
	return 0;
}
