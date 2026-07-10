#ifndef ORDENA_H
#define ORDENA_H

#include <stdio.h>
#include "arvore.h"

void ordenaVetor(void** vetor, int tamanho, int k, char* alg, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry);

void selectionSort(void** vetor, int n, int k, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);
void bubbleSort(void** vetor, int n, int k, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);
void insertionSort(void** vetor, int n, int k, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);
void shellSort(void** vetor, int n, int k, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);
void quickSort(void** vetor, int baixo, int alto, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);
void mergeSort(void** vetor, int l, int r, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

#endif