#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "arvore.h"
#include "forma.h"

int main() {
    printf("========== INICIANDO TESTE UNITÁRIO: arvore.c ==========\n");

    Figura f1 = criaCirculoStruct(10, 100.0, 50.0, 10.0, "black", "white");
    Figura f2 = criaCirculoStruct(20, 100.0, 20.0, 10.0, "black", "white"); 
    Figura f3 = criaCirculoStruct(30, 100.0, 80.0, 10.0, "black", "white");
    Figura f4 = criaCirculoStruct(40, 100.0, 10.0, 10.0, "black", "white");

    Arvore a = criaArvore();
    assert(contagemItens(a) == 0);
    printf("-> Estado inicial verificado (0 itens).\n");

    a = inserirNaArvore(a, f1);
    assert(contagemItens(a) == 1);

    a = inserirNaArvore(a, f2);
    a = inserirNaArvore(a, f3);
    a = inserirNaArvore(a, f4);
    
    assert(contagemItens(a) == 4);
    printf("-> Inserção de 4 elementos e contagem de itens verificadas.\n");

    void **vetor = malloc(4 * sizeof(void*));
    descarregaArvoreNoVetor(a, vetor);

    assert(getFormaId(vetor[0]) == 40);
    assert(getFormaId(vetor[1]) == 20);
    assert(getFormaId(vetor[2]) == 10); 
    assert(getFormaId(vetor[3]) == 30);
    printf("-> Percurso e descarregamento em vetor mantiveram a ordenação por Y com sucesso.\n");
    free(vetor);

    a = removeDaArvore(a, f4);
    assert(contagemItens(a) == 3);

    void **vetor2 = malloc(3 * sizeof(void*));
    descarregaArvoreNoVetor(a, vetor2);
    assert(getFormaId(vetor2[0]) == 20); 
    assert(getFormaId(vetor2[1]) == 10);
    assert(getFormaId(vetor2[2]) == 30);
    printf("-> Remoção de elemento e reestruturação da árvore verificadas.\n");
    free(vetor2);

    destroiArvoreApenasNos(a);
    liberaFigura(f1);
    liberaFigura(f2);
    liberaFigura(f3);
    liberaFigura(f4);

    printf("\n[RESULTADO]: TODOS OS ASSERTS DA ÁRVORE PASSARAM!\n");
    printf("========================================================\n");
    return 0;
}