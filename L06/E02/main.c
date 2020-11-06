#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int **malloc2dR(FILE *f, int *r, int *c){
	fscanf(f, "%d %d", r, c);
	int i, j;
	int **m = (int**) malloc(*r * sizeof(int*));
	for(i = 0; i < *r; ++i){
		m[i] = (int*) malloc(*c * sizeof(int));
		for(j = 0; j < *c; ++j)
			fscanf(f, "%d", &m[i][j]);
	}
	return m;
}

void separa(int **mat, int nr, int nc, int **bia, int **ner){
	int i, j, cntb = 0, cntn = 0;
	int hcb = ((nr*nc) % 2 == 0) ? nr*nc/2 : (nr*nc+1)/2;
	*bia = (int*) malloc(hcb * sizeof(int));
	*ner = (int*) malloc(hcb * sizeof(int));	
	for(i = 0; i < nr; ++i)
		for(j = 0; j < nc; ++j)
			if((i+j)%2 == 0)
				(*bia)[cntb++] = mat[i][j];
			else
				(*ner)[cntn++] = mat[i][j];
}

int main(int argc, char *argv[]){
	FILE *fp = fopen("mat.txt", "r");
	if(fp == NULL) exit(EXIT_FAILURE);

	int nr, nc, i, j, hcb;
	int **mat, *bianchi, *neri;

	mat = malloc2dR(fp, &nr, &nc);

	separa(mat, nr, nc, &bianchi, &neri);
	hcb = ((nr*nc) % 2 == 0) ? nr*nc/2 : (nr*nc+1)/2;
	
	printf("Matrice: \n");
	for(i = 0; i < nr; ++i){
		for(j = 0; j < nc; ++j)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
	printf("\n");

	printf("Bianchi: ");
	for(i = 0; i < hcb; ++i)
		printf("%d ", bianchi[i]);
	printf("\n\n");

	if(hcb%2 != 0) --hcb;
	
	printf("Neri: ");
	for(i = 0; i < hcb; ++i)
		printf("%d ", neri[i]);
	printf("\n\n");

	// Dealloca
	for(i = 0; i < nr; ++i)
		free(mat[i]);
	free(mat);
	free(bianchi);
	free(neri);

	return 0;
}
