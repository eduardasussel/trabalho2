#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "forma.h" 

typedef struct no {
    void* info;
    struct no* prox;
    struct no* ant;
} No;

typedef struct lista {
    No* primeiro;
    No* ultimo;
    int tamanho;
} StructLista;

Lista criaLista() {
    StructLista* l = malloc(sizeof(StructLista));
    if (l != NULL) {
        l->primeiro = NULL;
        l->ultimo = NULL;
        l->tamanho = 0;
    }
    return (Lista)l;
}

int tamanhoLista(Lista lista) {
    if (lista == NULL) return 0;
    StructLista* l = (StructLista*)lista;
    return l->tamanho;
}

void insereLista(Lista lista, void* item) {
    if (lista == NULL || item == NULL) return;
    StructLista* l = (StructLista*)lista;
    
    No* novo = malloc(sizeof(No));
    if (novo == NULL) return;
    
    novo->info = item;
    novo->prox = NULL;
    novo->ant = l->ultimo;
    
    if (l->primeiro == NULL) {
        l->primeiro = novo;
    } else {
        l->ultimo->prox = novo;
    }
    
    l->ultimo = novo;
    l->tamanho++;
}

Posicao primeiro(Lista lista) {
    if (lista == NULL) return NULL;
    StructLista* l = (StructLista*)lista;
    return (Posicao)l->primeiro;
}

Posicao proximo(Posicao pos) {
    if (pos == NULL) return NULL;
    No* n = (No*)pos;
    return (Posicao)n->prox;
}

void* getItem(Posicao pos) {
    if (pos == NULL) return NULL;
    No* n = (No*)pos;
    return n->info;
}

void removeItemPorPonteiro(Lista lista, void* item) {
    if (lista == NULL || item == NULL) return;
    StructLista* l = (StructLista*)lista;
    
    No* atual = l->primeiro;
    while (atual != NULL) {
        if (atual->info == item) { 
            if (atual->ant != NULL) {
                atual->ant->prox = atual->prox;
            } else {
                l->primeiro = atual->prox;
            }
            
            if (atual->prox != NULL) {
                atual->prox->ant = atual->ant;
            } else {
                l->ultimo = atual->ant;
            }
            
            No* apagar = atual;
            atual = atual->prox;
            free(apagar);
            l->tamanho--;
        } else {
            atual = atual->prox;
        }
    }
}

void liberaListaApenasNos(Lista lista) {
    if (lista == NULL) return;
    StructLista* l = (StructLista*)lista;
    
    No* atual = l->primeiro;
    while (atual != NULL) {
        No* prox = atual->prox;
        free(atual); 
        atual = prox;
    }
    
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->tamanho = 0;
    free(l);
}

void destroiListaCompleta(Lista lista) {
    if (lista == NULL) return;
    StructLista* l = (StructLista*)lista;
    
    No* atual = l->primeiro;
    while (atual != NULL) {
        No* prox = atual->prox;
        free(atual); 
        atual = prox;
    }
    free(l);
}

void* buscaFiguraPorId(Lista lista, int id) {
    if (lista == NULL) return NULL;
    
    for (Posicao pos = primeiro(lista); pos != NULL; pos = proximo(pos)) {
        void* f = getItem(pos);
        if (getFormaId(f) == id) { 
            return f;
        }
    }
    return NULL;
}