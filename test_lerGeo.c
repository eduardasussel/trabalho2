#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "arvore.h"
#include "forma.h"
#include "lerGeo.h"

void prepararArquivoGeoDeTeste(const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "w");
    if (!arq) {
        perror("Erro ao criar arquivo temporário de testes");
        exit(1);
    }
    
    fprintf(arq, "c 10 50.0 60.0 15.5 red blue\n");
    fprintf(arq, "r 20 10.0 20.0 200.0 100.0 green yellow\n");
    fprintf(arq, "l 30 0.0 0.0 100.0 100.0 black\n");
    fprintf(arq, "t 40 50.0 50.0 black white m Texto de Teste\n");
    
    fclose(arq);
}

int main() {
    printf("========== INICIANDO TESTE UNITÁRIO: lerArquivoGeo ==========\n");

    const char *nomeTestGeo = "teste_temporario.geo";
    prepararArquivoGeoDeTeste(nomeTestGeo);

    Arvore arvoreTestes = criaArvore();
    assert(contagemItens(arvoreTestes) == 0);

    arvoreTestes = lerArquivoGeo(".", (char*)nomeTestGeo, arvoreTestes);

    int totalFiguras = contagemItens(arvoreTestes);
    printf("Total de figuras inseridas na árvore: %d\n", totalFiguras);

    assert(totalFiguras == 4);

    void **vetorElementos = malloc(totalFiguras * sizeof(void*));
    descarregaArvoreNoVetor(arvoreTestes, vetorElementos);

    int achouCirculo = 0, achouRetangulo = 0;

    for (int i = 0; i < totalFiguras; i++) {
        void *fig = vetorElementos[i];
        int id = getFormaId(fig);
        char tipo = getFormaTipo(fig);

        if (id == 10) {
            assert(tipo == 'c');
            assert(getFormaR(fig) == 15.5);
            assert(strcmp(getFormaCorBorda(fig), "red") == 0);
            achouCirculo = 1;
        }
        else if (id == 20) {
            assert(tipo == 'r');
            assert(getFormaW(fig) == 200.0);
            assert(getFormaH(fig) == 100.0);
            achouRetangulo = 1;
        }
    }

    assert(achouCirculo == 1);
    assert(achouRetangulo == 1);

    free(vetorElementos);
    
    destroiArvoreApenasNos(arvoreTestes); 
    
    remove(nomeTestGeo);

    printf("\n[RESULTADO]: TODOS OS ASSERTS PASSARAM COM SUCESSO! \n");
    printf("=============================================================\n");
    return 0;
}