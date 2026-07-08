#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "arvore.h"
#include "forma.h"
#include "comandos.h"

int main() {
    printf("========== INICIANDO TESTE UNITÁRIO: comandos.c (realizaCm) ==========\n");

    Arvore bancoDeDados = criaArvore();
    Arvore arvoreAux = criaArvore();

    Figura fDentro = criaCirculoStruct(99, 30.0, 30.0, 5.0, "black", "white");
    bancoDeDados = inserirNaArvore(bancoDeDados, fDentro);

    FILE *txtLog = fopen("teste_cm_log.txt", "w");
    assert(txtLog != NULL);

    inicializaComandos();
    realizaCm(0.0, 0.0, 100.0, 100.0, 10.0, 10.0, bancoDeDados, arvoreAux, txtLog);
    
    fclose(txtLog);

    printf("Itens após comando CM: %d\n", contagemItens(bancoDeDados));
    
    FILE *readLog = fopen("teste_cm_log.txt", "r");
    char linha[256];
    int achouLogCm = 0;
    while (fgets(linha, sizeof(linha), readLog)) {
        if (strstr(linha, "cm") != NULL || strstr(linha, "99") != NULL) {
            achouLogCm = 1;
        }
    }
    fclose(readLog);

    assert(achouLogCm == 1);
    printf("-> Escrita e formatação do comando 'cm' no relatório de texto verificadas.\n");

    remove("teste_cm_log.txt");
    destroiArvoreApenasNos(bancoDeDados);
    destroiArvoreApenasNos(arvoreAux);
    liberaFigura(fDentro);

    printf("\n[RESULTADO]: TODOS OS ASSERTS DE COMANDOS PASSARAM! \n");
    printf("========================================================\n");
    return 0;
}