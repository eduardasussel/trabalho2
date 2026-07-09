#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "arvore.h"
#include "lista.h"
#include "forma.h"
#include "comandos.h"
#include "svg.h"
#include "lerGeo.h"

void extraiNomePuro(char *resultado, const char *origem) {
    const char *ultimoBarra = strrchr(origem, '/');
    if (!ultimoBarra) ultimoBarra = strrchr(origem, '\\');
    
    const char *base = ultimoBarra ? ultimoBarra + 1 : origem;
    
    strcpy(resultado, base);
    
    char *ponto = strrchr(resultado, '.');
    if (ponto) *ponto = '\0';
}

int main(int argc, char *argv[]) {
    char *bed = NULL;
    char *arqGeo = NULL;
    char *bsd = NULL;
    char *arqQry = NULL;
    
    int opt;

    while ((opt = getopt(argc, argv, "e:f:o:q:")) != -1) {
        switch (opt) {
            case 'e': bed = optarg; break;
            case 'f': arqGeo = optarg; break;
            case 'o': bsd = optarg; break;
            case 'q': arqQry = optarg; break;
            default:
                fprintf(stderr, "Uso: %s [-e bed] -f arq.geo -o bsd [-q arqcons.qry]\n", argv[0]);
                return 1;
        }
    }

    if (!arqGeo || !bsd) {
        fprintf(stderr, "Erro: Os parâmetros -f (arquivo .geo) e -o (diretório de saída) são obrigatórios.\n");
        return 1;
    }

    Arvore arvoreFormas = criaArvore(); 
    inicializaComandos();

    char caminhoGeoCompleto[1024] = "";
    if (bed) {
        sprintf(caminhoGeoCompleto, "%s/%s", bed, arqGeo);
    } else {
        strcpy(caminhoGeoCompleto, arqGeo);
    }

    char nomeGeoPuro[256];
    extraiNomePuro(nomeGeoPuro, arqGeo);

    arvoreFormas = lerArquivoGeo(bed, arqGeo,arvoreFormas);

    printf("[DEBUG MAIN] Banco de dados carregado com sucesso. Total de itens: %d\n", contagemItens(arvoreFormas));

    char svgGeoSaida[1024];
    sprintf(svgGeoSaida, "%s/%s.svg", bsd, nomeGeoPuro);
    FILE *svgPrincipal = iniciaSVG(svgGeoSaida);
    if (svgPrincipal) {
        int tamGeo = contagemItens(arvoreFormas);
        if (tamGeo > 0) {
            void** vetGeo = malloc(tamGeo * sizeof(void*));
            descarregaArvoreNoVetor(arvoreFormas, vetGeo);
            for (int i = 0; i < tamGeo; i++) {
                desenhaFiguraSVG(svgPrincipal, vetGeo[i]);
            }
            free(vetGeo);
        }
        finalizaSVG(svgPrincipal);
    }

    if (arqQry) {
        char caminhoQryCompleto[1024] = "";
        if (bed) {
            sprintf(caminhoQryCompleto, "%s/%s", bed, arqQry);
        } else {
            strcpy(caminhoQryCompleto, arqQry);
        }

        char nomeQryPuro[256];
        extraiNomePuro(nomeQryPuro, arqQry);

        char caminhoTxtSaida[1024], caminhoSvgSaida[1024];
        sprintf(caminhoTxtSaida, "%s/%s-%s.txt", bsd, nomeGeoPuro, nomeQryPuro);
        sprintf(caminhoSvgSaida, "%s/%s-%s.svg", bsd, nomeGeoPuro, nomeQryPuro);

        FILE *fTxt = fopen(caminhoTxtSaida, "w");
        FILE *fSvg = iniciaSVG(caminhoSvgSaida);

        FILE *fQry = fopen(caminhoQryCompleto, "r");
        if (fQry && fTxt && fSvg) {
            char cmdQry[10];

            Arvore arvoreFormasAux = criaArvore(); 

            while (fscanf(fQry, "%s", cmdQry) != EOF) {
                if (strcmp(cmdQry, "sel") == 0) {
                    double x, y, w, h;
                    fscanf(fQry, "%lf %lf %lf %lf", &x, &y, &w, &h);
                    realizaSel(x, y, w, h, arvoreFormasAux, arvoreFormas, fTxt);

                } else if (strcmp(cmdQry, "find") == 0) {
                    int k; char alg[5], crit[5]; double x, y, dw;
                    fscanf(fQry, "%d %s %s %lf %lf %lf", &k, alg, crit, &x, &y, &dw);
            
                    realizaFind(k, alg, crit, x, y, dw, arvoreFormasAux, bsd, nomeGeoPuro, nomeQryPuro, fTxt, fSvg);
                    
                } else if (strcmp(cmdQry, "mc") == 0) {
                    char corb[50], corp[50];
                    fscanf(fQry, "%s %s", corb, corp);
                    
                } else if (strcmp(cmdQry, "cm") == 0) {
                    double x, y, w, h, dx, dy;
                    fscanf(fQry, "%lf %lf %lf %lf %lf %lf", &x, &y, &w, &h, &dx, &dy);
                    realizaCm(x, y, w, h, dx, dy, arvoreFormas, arvoreFormasAux, fTxt);
                    
                } else if (strcmp(cmdQry, "findrm") == 0) {
                    int k; char alg[5], crit[5]; double x, y, dw;
                    fscanf(fQry, "%d %s %s %lf %lf %lf", &k, alg, crit, &x, &y, &dw);
                    realizaFindRm(k, alg, crit, x, y, dw, arvoreFormas, arvoreFormasAux, bsd, nomeGeoPuro, nomeQryPuro, fTxt, fSvg);
                }
            }
            
            fclose(fQry);
            fclose(fTxt);
            finalizaSVG(fSvg);
        } else {
            if (fQry) fclose(fQry);
            if (fTxt) fclose(fTxt);
            if (fSvg) finalizaSVG(fSvg);
            fprintf(stderr, "Erro ao processar arquivos de consulta do .qry\n");
        }
    }

    printf("Processamento concluído com sucesso.\n");
    return 0;
}