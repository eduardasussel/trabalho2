#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "ordena.h"
#include "forma.h"

int main() {
    printf("========== INICIANDO TESTE UNITÁRIO: ordena.c ==========\n");

    Figura f1 = criaRetanguloStruct(1, 0.0, 0.0, 300.0, 50.0, "black", "white");
    Figura f2 = criaRetanguloStruct(2, 0.0, 0.0, 100.0, 50.0, "black", "white");
    Figura f3 = criaRetanguloStruct(3, 0.0, 0.0, 200.0, 50.0, "black", "white");

    int n = 3;
    void **vetor = malloc(n * sizeof(void*));
    vetor[0] = f1;
    vetor[1] = f2;
    vetor[2] = f3;

    printf("-> Vetor inicial montado (Desordenado por largura).\n");

    ordenaVetor(vetor, n, "ss", "w", ".", "testGeo", "testQry");

    assert(getFormaId(vetor[0]) == 2);
    assert(getFormaId(vetor[1]) == 3);
    assert(getFormaId(vetor[2]) == 1);
    printf("-> Algoritmo reorganizou os ponteiros opacos corretamente pelo critério 'w'.\n");

    free(vetor);
    liberaFigura(f1);
    liberaFigura(f2);
    liberaFigura(f3);

    remove("./testGeo-testQry000001.svg");
    remove("./testGeo-testQry000002.svg");

    printf("\n[RESULTADO]: TODOS OS ASSERTS DE ORDENAÇÃO PASSARAM! \n");
    printf("========================================================\n");
    return 0;
}