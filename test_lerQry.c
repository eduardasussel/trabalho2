#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "lerQry.h"
#include "forma.h"

void prepararArquivoQryDeTeste(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "w");
    if (!arq) {
        perror("Erro ao criar arquivo .qry temporario");
        exit(1);
    }
    
    fprintf(arq, "find 2 quick a 50.0 50.0 10.0\n");
    fprintf(arq, "cm 10.0 10.0 100.0 100.0 5.0 5.0\n");
    fprintf(arq, "findrm 1 bubble w 0.0 0.0 500.0\n");
    fclose(arq);
}

int main() {
    printf("========== INICIANDO TESTE UNITÁRIO: lerQry.c ==========\n");

    const char *nomeTestQry = "teste_consultas.qry";
    prepararArquivoQryDeTeste(nomeTestQry);

    Arvore bancoDeDados = criaArvore();
    Lista listaPoligonos = criaLista();

    Figura f = criaCirculoStruct(1, 50.0, 50.0, 10.0, "blue", "red");
    bancoDeDados = inserirNaArvore(bancoDeDados, f);

    lerArquivoQry(".", (char*)nomeTestQry, ".", "mock_geo.geo", bancoDeDados, listaPoligonos);

    FILE *checkTxt = fopen("mock_geo-teste_consultas.txt", "r");
    FILE *checkSvg = fopen("mock_geo-teste_consultas.svg", "r");

    assert(checkTxt != NULL);
    assert(checkSvg != NULL);
    printf("-> Arquivos de saída agregados (.txt e .svg) criados com sucesso.\n");

    if (checkTxt) fclose(checkTxt);
    if (checkSvg) fclose(checkSvg);

    remove(nomeTestQry);
    remove("mock_geo-teste_consultas.txt");
    remove("mock_geo-teste_consultas.svg");
    
    destroiArvoreApenasNos(bancoDeDados);
    liberaFigura(f);

    printf("\n[RESULTADO]: TODOS OS ASSERTS DO LERQRY PASSARAM!\n");
    printf("========================================================\n");
    return 0;
}