#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lerGeo.h"
#include "forma.h"    

Arvore lerArquivoGeo(char *bed, char *nomeArq, Arvore arvoreFormas) {
    char caminhoCompleto[512];
    sprintf(caminhoCompleto, "%s/%s", bed, nomeArq);

    FILE *arq = fopen(caminhoCompleto, "r");
    if (!arq) {
        printf("Erro: Nao foi possivel abrir %s\n", caminhoCompleto);
        return arvoreFormas;
    }

    char comando[10];
    while (fscanf(arq, "%s", comando) != EOF) {
        
        if (strcmp(comando, "c") == 0) {
            int id; double x, y, r; 
            char corb[30], corp[30];
            fscanf(arq, "%d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
            Figura f = criaCirculoStruct(id, x, y, r, corb, corp);

            arvoreFormas = inserirNaArvore(arvoreFormas, f);
        } 
        
        else if (strcmp(comando, "r") == 0) {
            int id; double x, y, w, h; 
            char corb[30], corp[30];
            fscanf(arq, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);
            Figura f = criaRetanguloStruct(id, x, y, w, h, corb, corp);

            arvoreFormas = inserirNaArvore(arvoreFormas, f);
        }

        else if (strcmp(comando, "l") == 0) {
            int id; double x1, y1, x2, y2; char cor[30];
            if (fscanf(arq, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor) == 6) {
            Figura f = criaLinhaStruct(id, x1, y1, x2, y2, cor);

            arvoreFormas = inserirNaArvore(arvoreFormas, f);
    }
}

        else if (strcmp(comando, "t") == 0) {
            int id; double x, y;
            char corb[30], corp[30], txt[100], ancora;
            fscanf(arq, "%d %lf %lf %s %s %c %[^\n]", &id, &x, &y, corb, corp, &ancora, txt);
            Figura f = criaTextoStruct(id, x, y, corb, corp, ancora, txt);

            arvoreFormas = inserirNaArvore(arvoreFormas, f);
        }

        else if (strcmp(comando, "ts") == 0) {
            char fFamily[50], fWeight[50], fSize[50];
            fscanf(arq, "%s %s %s", fFamily, fWeight, fSize);
        }
    }

    printf("Leitura GEO concluida. %d figuras carregadas.\n", contagemItens(arvoreFormas));
    fclose(arq);
    return arvoreFormas;
}