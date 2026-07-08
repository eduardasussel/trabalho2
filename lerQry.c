#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerQry.h"
#include "comandos.h"
#include "forma.h"
#include "lista.h"
#include "arvore.h"
#include "svg.h"

static void extraiNomePuroQry(char *resultado, const char *origem) {
    const char *ultimoBarra = strrchr(origem, '/');
    if (!ultimoBarra) ultimoBarra = strrchr(origem, '\\');
    const char *base = ultimoBarra ? ultimoBarra + 1 : origem;
    
    strcpy(resultado, base);
    char *ponto = strrchr(resultado, '.');
    if (ponto) *ponto = '\0';
}

void lerArquivoQry(char *bed, char *nomeArq, char *pathSaida, char *nomeGeoOrig, Arvore bancoDeDados, Lista listaPoligonos) {
    char caminhoCompleto[512];
    if (bed && strlen(bed) > 0) {
        sprintf(caminhoCompleto, "%s/%s", bed, nomeArq);
    } else {
        strcpy(caminhoCompleto, nomeArq);
    }

    FILE *arq = fopen(caminhoCompleto, "r");
    if (!arq) {
        printf("Erro: Nao foi possivel abrir %s\n", caminhoCompleto);
        return;
    }

    char nomeQryPuro[256];
    char nomeGeoPuro[256];
    extraiNomePuroQry(nomeQryPuro, nomeArq);
    extraiNomePuroQry(nomeGeoPuro, nomeGeoOrig);

    char caminhoSVG[1024];
    char caminhoTXT[1024];

    sprintf(caminhoSVG, "%s/%s-%s.svg", pathSaida, nomeGeoPuro, nomeQryPuro);
    sprintf(caminhoTXT, "%s/%s-%s.txt", pathSaida, nomeGeoPuro, nomeQryPuro);

    FILE *svg = iniciaSVG(caminhoSVG);
    FILE *txt = fopen(caminhoTXT, "w");
    
    char comando[10];

    Arvore arvoreFormasAux = criaArvore();

    while (fscanf(arq, "%s", comando) != EOF) {
        printf("Executando comando: %s\n", comando);

        if (strcmp(comando, "find") == 0) {
            int k; char alg[5], crit[5]; double fx, fy, fdw;
            fscanf(arq, "%d %s %s %lf %lf %lf", &k, alg, crit, &fx, &fy, &fdw);

            realizaFind(k, alg, crit, fx, fy, fdw, arvoreFormasAux, pathSaida, nomeGeoPuro, nomeQryPuro, txt, svg);

        } else if (strcmp(comando, "cm") == 0) {
            double cx, cy, cw, ch, cdx, cdy;
            fscanf(arq, "%lf %lf %lf %lf %lf %lf", &cx, &cy, &cw, &ch, &cdx, &cdy);
            
            realizaCm(cx, cy, cw, ch, cdx, cdy, bancoDeDados, arvoreFormasAux, txt);

        } else if (strcmp(comando, "findrm") == 0) {
            int k; char alg[5], crit[5]; double fx, fy, fdw;
            fscanf(arq, "%d %s %s %lf %lf %lf", &k, alg, crit, &fx, &fy, &fdw);
            
            realizaFindRm(k, alg, crit, fx, fy, fdw, bancoDeDados, arvoreFormasAux, pathSaida, nomeGeoPuro, nomeQryPuro, txt, svg);

        }
    }
    destroiArvoreApenasNos(arvoreFormasAux);

    finalizaSVG(svg); 
    fclose(txt);
    fclose(arq);
}