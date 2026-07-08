#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdio.h>
#include "arvore.h"

void inicializaComandos();
void realizaSel(double x, double y, double w, double h, Arvore arvoreFormas, Arvore raiz, FILE *txt);
void realizaFind(int k, char* alg, char* crit, double x, double y, double dw, Arvore arvoreFormas, char* pathSaida, char* nomeGeo, char* nomeQry, FILE *txt, FILE *svg);
void realizaCm(double x, double y, double w, double h, double dx, double dy, Arvore bancoDeDados, Arvore arvoreFormas, FILE *txt);
void realizaFindRm(int k, char* alg, char* crit, double x, double y, double dw, Arvore bancoDeDados, Arvore arvoreFormas, char* pathSaida, char* nomeGeo, char* nomeQry, FILE *txt, FILE *svg);
void realizaMc(char* corb, char* corp, Arvore arvoreFormas);

#endif