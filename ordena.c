#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordena.h"
#include "forma.h"
#include "svg.h"

static void gerarSnapshot(void** vetor, int tamanhoTotal, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame);

static void trocar(void** a, void** b) {
    void* temp = *a;
    *a = *b;
    *b = temp;
}

void ordenaVetor(void** vetor, int tamanho, char* alg, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry) {
    int numFrame = 1; 

    if (strcmp(alg, "ss") == 0) {
        selectionSort(vetor, tamanho, crit, pathSaida, nomeGeo, nomeQry, &numFrame);
    } else if (strcmp(alg, "bs") == 0) {
        bubbleSort(vetor, tamanho, crit, pathSaida, nomeGeo, nomeQry, &numFrame);
    } else if (strcmp(alg, "is") == 0) {
        insertionSort(vetor, tamanho, crit, pathSaida, nomeGeo, nomeQry, &numFrame);
    } else if (strcmp(alg, "shs") == 0) {
        shellSort(vetor, tamanho, crit, pathSaida, nomeGeo, nomeQry, &numFrame);
    } else if (strcmp(alg, "qs") == 0) {
        quickSort(vetor, 0, tamanho - 1, tamanho, crit, pathSaida, nomeGeo, nomeQry, &numFrame);
    } else if (strcmp(alg, "ms") == 0) {
        mergeSort(vetor, 0, tamanho - 1, tamanho, crit, pathSaida, nomeGeo, nomeQry, &numFrame);
    }
}

void selectionSort(void** vetor, int n, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (comparaFiguras(vetor[j], vetor[min_idx], crit) < 0) {
                min_idx = j;
            }
        }
        trocar(&vetor[min_idx], &vetor[i]);

        gerarSnapshot(vetor, n, pathSaida, nomeGeo, nomeQry, numFrame);
    }
}

void bubbleSort(void** vetor, int n, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (comparaFiguras(vetor[j], vetor[j + 1], crit) > 0) {
                trocar(&vetor[j], &vetor[j + 1]);
                trocou = 1;
            }
        }
        gerarSnapshot(vetor, n, pathSaida, nomeGeo, nomeQry, numFrame);
        
        if (!trocou) break;
    }
}

void insertionSort(void** vetor, int n, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    for (int i = 1; i < n; i++) {
        void* chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && comparaFiguras(vetor[j], chave, crit) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;

        gerarSnapshot(vetor, n, pathSaida, nomeGeo, nomeQry, numFrame);
    }
}

void shellSort(void** vetor, int n, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            void* temp = vetor[i];
            int j;
            for (j = i; j >= gap && comparaFiguras(vetor[j - gap], temp, crit) > 0; j -= gap) {
                vetor[j] = vetor[j - gap];
            }
            vetor[j] = temp;
        }
        gerarSnapshot(vetor, n, pathSaida, nomeGeo, nomeQry, numFrame);
    }
}

static int particionar(void** vetor, int baixo, int alto, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    void* pivo = vetor[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (comparaFiguras(vetor[j], pivo, crit) < 0) {
            i++;
            trocar(&vetor[i], &vetor[j]);
        }
    }
    trocar(&vetor[i + 1], &vetor[alto]);
    
    gerarSnapshot(vetor, tamanhoTotal, pathSaida, nomeGeo, nomeQry, numFrame); 
    
    return (i + 1);
}

void quickSort(void** vetor, int baixo, int alto, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    if (baixo < alto) {
        int pi = particionar(vetor, baixo, alto, tamanhoTotal, crit, pathSaida, nomeGeo, nomeQry, numFrame);
        quickSort(vetor, baixo, pi - 1, tamanhoTotal, crit, pathSaida, nomeGeo, nomeQry, numFrame);
        quickSort(vetor, pi + 1, alto, tamanhoTotal, crit, pathSaida, nomeGeo, nomeQry, numFrame);
    }
}

static void merge(void** vetor, int l, int m, int r, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    int n1 = m - l + 1;
    int n2 = r - m;

    void** L = malloc(n1 * sizeof(void*));
    void** R = malloc(n2 * sizeof(void*));

    for (int i = 0; i < n1; i++) L[i] = vetor[l + i];
    for (int j = 0; j < n2; j++) R[j] = vetor[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (comparaFiguras(L[i], R[j], crit) <= 0) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);

    gerarSnapshot(vetor, tamanhoTotal, pathSaida, nomeGeo, nomeQry, numFrame);
}

void mergeSort(void** vetor, int l, int r, int tamanhoTotal, char* crit, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(vetor, l, m, tamanhoTotal, crit, pathSaida, nomeGeo, nomeQry, numFrame);
        mergeSort(vetor, m + 1, r, tamanhoTotal, crit, pathSaida, nomeGeo, nomeQry, numFrame);
        merge(vetor, l, m, r, tamanhoTotal, crit, pathSaida, nomeGeo, nomeQry, numFrame);
    }
}

static void gerarSnapshot(void** vetor, int tamanhoTotal, char* pathSaida, char* nomeGeo, char* nomeQry, int* numFrame) {
    char caminhoFrame[1024];
    
    snprintf(caminhoFrame, sizeof(caminhoFrame), "%s/%s-%s%06d.svg", pathSaida, nomeGeo, nomeQry, *numFrame);
    
    FILE* svgFrame = iniciaSVG(caminhoFrame);
    if (svgFrame != NULL) {
        for (int i = 0; i < tamanhoTotal; i++) {
            desenhaFiguraSVG(svgFrame, vetor[i]);
        }
        finalizaSVG(svgFrame); 
    }
    
    (*numFrame)++; 
}