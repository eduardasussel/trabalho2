#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include "lista.h"

typedef void* Arvore;
typedef void* Figura;

Arvore criaArvore();
Arvore inserirNaArvore(Arvore raiz, Figura nova_figura);
Arvore removeDaArvore(Arvore raiz, Figura figura);

int contagemItens(Arvore raiz);
void descarregaArvoreNoVetor(Arvore raiz, void** vetor);
void desmarcarTodasAsFiguras(Arvore raiz);
void filtrarFigurasNaRegiao(Arvore raiz, double x, double y, double w, double h, Arvore* arvoreFormas, FILE *txt);
void buscarFigurasNaRegiaoArvore(Arvore raiz, double x, double y, double w, double h, Lista listaDestino);
void alterarCoresArvore(Arvore arvore, char* corb, char* corp);
void destroiArvoreApenasNos(Arvore raiz);
void liberaArvore(Arvore raiz);

#endif