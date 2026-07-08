#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "forma.h"
#include "lista.h"

typedef struct no {
    Figura info;
    struct no *esq;
    struct no *dir;
} No;

Arvore criaArvore() {
    return NULL;
}

Arvore inserirNaArvore(Arvore raiz, Figura nova_figura) {
    No* atual = (No*) raiz;

    if (atual == NULL) {
        No* novo = (No*) malloc(sizeof(No));
        if (novo == NULL) return NULL;
        novo->info = nova_figura;
        novo->esq = NULL;
        novo->dir = NULL;
        return (Arvore) novo;
    }

    if (getFormaY(nova_figura) < getFormaY(atual->info)) {
        atual->esq = (No*) inserirNaArvore(atual->esq, nova_figura);
    } else {
        atual->dir = (No*) inserirNaArvore(atual->dir, nova_figura);
    }

    return (Arvore) atual;
}

static int contagemItensRecursivo(No* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contagemItensRecursivo(raiz->esq) + contagemItensRecursivo(raiz->dir);
}

int contagemItens(Arvore raiz) {
    return contagemItensRecursivo((No*) raiz);
}

static void descarregaRecursivo(No* raiz, void** vetor, int* indice) {
    if (raiz == NULL) return;
    descarregaRecursivo(raiz->esq, vetor, indice);
    vetor[*indice] = raiz->info;
    (*indice)++;
    descarregaRecursivo(raiz->dir, vetor, indice);
}

void descarregaArvoreNoVetor(Arvore raiz, void** vetor) {
    int indice = 0;
    descarregaRecursivo((No*) raiz, vetor, &indice);
}


static void desmarcarRecursivo(No* raiz) {
    if (raiz == NULL) return;
    setFiguraSelecionada(raiz->info, 0); 
    desmarcarRecursivo(raiz->esq);
    desmarcarRecursivo(raiz->dir);
}

void desmarcarTodasAsFiguras(Arvore raiz) {
    desmarcarRecursivo((No*) raiz);
}

static void filtrarFigurasNaRegiaoRecursiva(No* raiz, double x, double y, double w, double h, Arvore* arvoreFormas, FILE *txt) {
    if (raiz == NULL) return;

    filtrarFigurasNaRegiaoRecursiva(raiz->esq, x, y, w, h, arvoreFormas, txt);

    void* figura = raiz->info; 
    if (estaDentroDaRegiao(figura, x, y, w, h)) {
        *arvoreFormas = inserirNaArvore(*arvoreFormas, figura); 
        setFiguraSelecionada(figura, 1);
        
        fprintf(txt, "ID: %d, Tipo: %c selecionado.\n", 
                getFormaId(figura), getFormaTipo(figura));
    }

    filtrarFigurasNaRegiaoRecursiva(raiz->dir, x, y, w, h, arvoreFormas, txt);
}

void filtrarFigurasNaRegiao(Arvore raiz, double x, double y, double w, double h, Arvore arvoreFormas, FILE *txt) {
    No* raiz_real = (No*) raiz; 

    Arvore temp = arvoreFormas;
    filtrarFigurasNaRegiaoRecursiva(raiz_real, x, y, w, h, &temp, txt);
}

static void buscarFigurasNaRegiaoArvoreRecursiva(No* raiz, double x, double y, double w, double h, Lista listaDestino) {
    if (raiz == NULL) return;
    buscarFigurasNaRegiaoArvoreRecursiva(raiz->esq, x, y, w, h, listaDestino);
    
    if (estaDentroDaRegiao(raiz->info, x, y, w, h)) {
        insereLista(listaDestino, raiz->info);
    }
    
    buscarFigurasNaRegiaoArvoreRecursiva(raiz->dir, x, y, w, h, listaDestino);
}

void buscarFigurasNaRegiaoArvore(Arvore raiz, double x, double y, double w, double h, Lista listaDestino) {
    buscarFigurasNaRegiaoArvoreRecursiva((No*) raiz, x, y, w, h, listaDestino);
}


static void alteraCoresRecursivo(No* raiz, char* corb, char* corp) {
    if (raiz == NULL) return;

    void* figura = raiz->info; 
    setFormaCorBorda(figura, corb);
    setFormaCorPreenchimento(figura, corp);

    alteraCoresRecursivo(raiz->esq, corb, corp);
    alteraCoresRecursivo(raiz->dir, corb, corp);
}

void alterarCoresArvore(Arvore arvore, char* corb, char* corp) {
    alteraCoresRecursivo((No*) arvore, corb, corp);
}


static No* encontrarMinimo(No* raiz) {
    No* atual = raiz;
    while (atual && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

No* removeDaArvoreRecursivo(No* raiz, Figura figura) {
    if (raiz == NULL) return NULL;

    if (getFormaY(figura) < getFormaY(raiz->info)) {
        raiz->esq = removeDaArvoreRecursivo(raiz->esq, figura);
    } else if (getFormaY(figura) > getFormaY(raiz->info)) {
        raiz->dir = removeDaArvoreRecursivo(raiz->dir, figura);
    } else {
        if (raiz->info != figura) {
            raiz->dir = removeDaArvoreRecursivo(raiz->dir, figura);
            return raiz;
        }

        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        No* temp = encontrarMinimo(raiz->dir);
        raiz->info = temp->info;
        raiz->dir = removeDaArvoreRecursivo(raiz->dir, temp->info);
    }
    return raiz;
}

Arvore removeDaArvore(Arvore raiz, Figura figura) {
    return (Arvore) removeDaArvoreRecursivo((No*) raiz, figura);
}

void destroiArvoreApenasNos(Arvore raiz) {
    No* n = (No*) raiz;
    if (n == NULL) return;
    destroiArvoreApenasNos((Arvore) n->esq);
    destroiArvoreApenasNos((Arvore) n->dir);
    free(n);
}

void liberaArvore(Arvore raiz) {
    No* n = (No*) raiz;
    if (n == NULL) return;
    liberaArvore((Arvore) n->esq);
    liberaArvore((Arvore) n->dir);
    liberaFigura(n->info); 
    free(n);
}