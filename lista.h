#ifndef LISTA_H
#define LISTA_H

typedef void* Lista;
typedef void* Posicao;

Lista criaLista();
int tamanhoLista(Lista lista);

void insereLista(Lista lista, void* item);
void removeItemPorPonteiro(Lista lista, void* item);

Posicao primeiro(Lista lista);
Posicao proximo(Posicao pos);
void* getItem(Posicao pos);

void liberaListaApenasNos(Lista lista);
void destroiListaCompleta(Lista lista);

void* buscaFiguraPorId(Lista lista, int id);

#endif