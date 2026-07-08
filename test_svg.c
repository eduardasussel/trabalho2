#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "svg.h"
#include "forma.h"

int main() {
    printf("========== INICIANDO TESTE UNITÁRIO: svg.c ==========\n");

    const char *nomeTestSvg = "teste_grafico.svg";

    FILE *svg = iniciaSVG(nomeTestSvg);
    assert(svg != NULL);

    Figura retangulo = criaRetanguloStruct(55, 10.0, 20.0, 150.0, 80.0, "blue", "red");
    assert(retangulo != NULL);

    desenhaFiguraSVG(svg, retangulo);
    finalizaSVG(svg);

    FILE *leitura = fopen(nomeTestSvg, "r");
    assert(leitura != NULL);

    char linha[256];
    int encontrouTagRetangulo = 0;
    int encontrouIdOuDados = 0;

    while (fgets(linha, sizeof(linha), leitura)) {
        if (strstr(linha, "<rect") != NULL || strstr(linha, "rect") != NULL) {
            encontrouTagRetangulo = 1;
        }
        if (strstr(linha, "150") != NULL || strstr(linha, "80") != NULL) {
            encontrouIdOuDados = 1;
        }
    }
    fclose(leitura);

    assert(encontrouTagRetangulo == 1);
    assert(encontrouIdOuDados == 1);
    printf("-> Escrita de tags e propriedades geométricas no SVG validadas com sucesso.\n");

    liberaFigura(retangulo);
    remove(nomeTestSvg);

    printf("\n[RESULTADO]: TODOS OS ASSERTS DO SVG PASSARAM! \n");
    printf("====================================================\n");
    return 0;
}