#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"
#include "forma.h"
#include "arvore.h"
#include "lista.h"
#include "ordena.h"
#include "svg.h"

static Arvore arvoreFormas = NULL; 

void inicializaComandos() {
    if (arvoreFormas != NULL) {
        liberaArvore(arvoreFormas);
    }
    arvoreFormas = criaArvore();
}

void realizaSel(double x, double y, double w, double h, Arvore* arvoreAuxiliar, Arvore bancoDeDados, FILE *txt) { 
    destroiArvoreApenasNos(*arvoreAuxiliar);
    desmarcarTodasAsFiguras(bancoDeDados);
    
    filtrarFigurasNaRegiao(bancoDeDados, x, y, w, h, arvoreAuxiliar, txt);
    
    fprintf(txt, "\n");
    printf("Seleção concluída. %d figuras selecionadas.\n", contagemItens(*arvoreAuxiliar));
}

void realizaFind(int k, char* alg, char* crit, double x, double y, double dw, Arvore arvoreFormas, char* pathSaida, char* nomeGeo, char* nomeQry, FILE *txt, FILE *svg) {
    int tamanho = contagemItens(arvoreFormas);
    if (tamanho == 0) return;

    void** vetor = malloc(tamanho * sizeof(void*));
    descarregaArvoreNoVetor(arvoreFormas, vetor);

    ordenaVetor(vetor, tamanho, k, alg, crit, pathSaida, nomeGeo, nomeQry);

    fprintf(txt, "=== COMANDO FIND: %d PRIMEIROS ORDENADOS ===\n", k);
    
    double posX = x;
    int limite = (k < tamanho) ? k : tamanho;
    
    for (int i = 0; i < limite; i++) {
        void* figura = vetor[i];
        
        setAncoraFigura(figura, posX, y);
        fprintf(txt, "Rank %d -> ID: %d, Tipo: %c\n", i + 1, getFormaId(figura), getFormaTipo(figura));
        desenhaRetanguloSel(svg, posX, y, 4, 4); 

        posX += dw; 
    }
    fprintf(txt, "============================================\n\n");

    free(vetor);
}

void realizaCm(double x, double y, double w, double h, double dx, double dy, Arvore bancoDeDados, Arvore arvoreFormas, FILE *txt) {
    desmarcarTodasAsFiguras(arvoreFormas); 
    destroiArvoreApenasNos(arvoreFormas); 

    Lista originaisNaRegiao = criaLista();
    
    buscarFigurasNaRegiaoArvore(bancoDeDados, x, y, w, h, originaisNaRegiao);

    for (Posicao pos = primeiro(originaisNaRegiao); pos != NULL; pos = proximo(pos)) {
        void* figuraOriginal = getItem(pos);

        void* figuraClone = clonaFigura(figuraOriginal);
        if (figuraClone == NULL) continue;

        double cx, cy;
        getAncoraFigura(figuraOriginal, &cx, &cy);
        setAncoraFigura(figuraClone, cx + dx, cy + dy);

        setFiguraSelecionada(figuraClone, 1);

        inserirNaArvore(bancoDeDados, figuraClone);
        inserirNaArvore(arvoreFormas, figuraClone);

        fprintf(txt, "Figura clonada. Original ID: %d -> Clone inserido em (%.2f, %.2f)\n", 
                getFormaId(figuraOriginal), cx + dx, cy + dy);
    }

    liberaListaApenasNos(originaisNaRegiao); 
}

void realizaFindRm(int k, char* alg, char* crit, double x, double y, double dw, Arvore bancoDeDados, Arvore arvoreFormas, char* pathSaida, char* nomeGeo, char* nomeQry, FILE *txt, FILE *svg) {
    int tamanho = contagemItens(arvoreFormas);
    if (tamanho == 0) return;

    void** vetor = malloc(tamanho * sizeof(void*));
    descarregaArvoreNoVetor(arvoreFormas, vetor);
    
    ordenaVetor(vetor, tamanho, k, alg, crit, pathSaida, nomeGeo, nomeQry);

    fprintf(txt, "=== COMANDO FINDRM: MANUTENÇÃO DOS %d PRIMEIROS ===\n", k);

    double posX = x;
    for (int i = 0; i < tamanho; i++) {
        void* figura = vetor[i];

        if (i < k) {
            setAncoraFigura(figura, posX, y);
            fprintf(txt, "Mantido [Rank %d] - ID: %d, Tipo: %c\n", i + 1, getFormaId(figura), getFormaTipo(figura));
            desenhaRetanguloSel(svg, posX, y, 4, 4);
            posX += dw;
        } else {
            fprintf(txt, "REMOVIDO (Rank %d > %d) - ID: %d, Tipo: %c\n", i + 1, k, getFormaId(figura), getFormaTipo(figura));
            removeDaArvore(bancoDeDados, figura);
            liberaFigura(figura); 
        }
    }
    fprintf(txt, "===================================================\n\n");

    destroiArvoreApenasNos(arvoreFormas);
    for (int i = 0; i < k && i < tamanho; i++) {
        inserirNaArvore(arvoreFormas, vetor[i]);
    }

    free(vetor);
}

void realizaMc(char* corb, char* corp, Arvore arvoreFormas) {
    alterarCoresArvore(arvoreFormas, corb, corp);
}