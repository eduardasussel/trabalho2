#ifndef ORDENA_H
#define ORDENA_H

void ordenaVetor(void** vetor, int tamanho, char* alg, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry);

void selectionSort(void** vetor, int n, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

void bubbleSort(void** vetor, int n, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

void insertionSort(void** vetor, int n, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

void shellSort(void** vetor, int n, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

static int particionar(void** vetor, int baixo, int alto, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

void quickSort(void** vetor, int baixo, int alto, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

static void merge(void** vetor, int l, int m, int r, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

void mergeSort(void** vetor, int l, int r, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

void ordenaVetor(void** vetor, int tamanho, char* alg, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry);

static void gerarSnapshot(void** vetor, int tamanhoTotal, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

#endif