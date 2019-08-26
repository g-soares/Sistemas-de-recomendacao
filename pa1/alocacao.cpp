#include"alocacao.h"
#include<stdlib.h>

double **alocaMatriz(int linhas, int colunas){
	double **matriz;
	matriz =(double**) calloc(linhas,sizeof(double*));
	for(int aux = 0; aux < linhas; aux++){
		matriz[aux] = alocaVetor(colunas);
	}
	return matriz;
}

double *alocaVetor(int tamanho){
	return (double*) calloc(tamanho,sizeof(double));
}

void desalocaMatriz(int linhas, double **matriz){
	for(int aux = 0; aux < linhas; aux++){
		desalocaVetor(matriz[aux]);
	}
	free(matriz);
	matriz = NULL;
}

void desalocaVetor(double *vetor){
	free(vetor);
	vetor = NULL;
}