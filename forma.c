#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forma.h"
#include "arvore.h"
#include "lista.h"


struct forma {
    char tipo;
    int id;
    double x, y, r, w, h;
    double x2, y2;        
    char texto[100];      
    char corb[30];
    char corp[30];
    char ancora;
    int selecionada;
};

double getFormaX1(void* fig) {
    return ((struct forma*)fig)->x;
}

double getFormaY1(void* fig) {
    return ((struct forma*)fig)->y;
}

double getFormaX2(void* fig) {
    return ((struct forma*)fig)->x2;
}

double getFormaY2(void* fig) {
    return ((struct forma*)fig)->y2;
}

double getFormaW(void* fig) {
    return ((struct forma*)fig)->w;
}

double getFormaH(void* fig) {
    return ((struct forma*)fig)->h;
}

double getFormaR(void* fig) {
    return ((struct forma*)fig)->r;
}

char getFormaTipo(void* fig) {
    return ((struct forma*)fig)->tipo;
}

int getFormaId(void* fig) {
    return ((struct forma*)fig)->id;
}

char* getFormaCorPreenchimento(void* fig) {
    return ((struct forma*)fig)->corp;
}

char* getFormaCorBorda(void* fig) {
    return ((struct forma*)fig)->corb;
}

char* getFormaTexto(Figura f) {
    struct forma *fig = (struct forma*) f;
    return fig->texto;
}

char getFormaAncora(Figura f) {
    struct forma *fig = (struct forma*) f; 
    return fig->ancora;
}

double getFormaY(void* fig) {
    double x, y;
    getAncoraFigura(fig, &x, &y);
    return y;
}

void setFormaX1(void* fig, double x) {
    ((struct forma*)fig)->x = x;
}

void setFormaY1(void* fig, double y) {
    ((struct forma*)fig)->y = y;
}

void setFormaX2(void* fig, double x2) {
    ((struct forma*)fig)->x2 = x2;
}

void setFormaY2(void* fig, double y2) {
    ((struct forma*)fig)->y2 = y2;
}

void setFormaCorBorda(void* fig, char* cor) {
    if (cor != NULL) {
        memset(((struct forma*)fig)->corb, 0, 30);
        strncpy(((struct forma*)fig)->corb, cor, 29);
        ((struct forma*)fig)->corb[29] = '\0'; 
    }
}

void setFormaCorPreenchimento(void* fig, char* cor) {
    if (cor != NULL) {
        memset(((struct forma*)fig)->corp, 0, 30);
        strncpy(((struct forma*)fig)->corp, cor, 29);
        ((struct forma*)fig)->corp[29] = '\0'; 
    }
}

void setAncoraFigura(void* fig, double x, double y) {
    struct forma* f = (struct forma*) fig;
    if (f == NULL) return;

    if (f->tipo == 'l') {
        double dx = f->x2 - f->x;
        double dy = f->y2 - f->y;
        f->x = x;
        f->y = y;
        f->x2 = x + dx;
        f->y2 = y + dy;
    } else {
        f->x = x;
        f->y = y;
    }
}

Figura criaCirculoStruct(int id, double x, double y, double r, char* corb, char* corp) {
    struct forma *f = (struct forma*) malloc(sizeof(struct forma));
    f->id = id;
    f->tipo = 'c';
    f->x = x;
    f->y = y;
    f->r = r;
    f->selecionada = 0;
    setFormaCorBorda(f, corb);
    setFormaCorPreenchimento(f, corp);
    return (Figura)f;
}

Figura criaRetanguloStruct(int id, double x, double y, double w, double h, char* corb, char* corp) {
    struct forma *f = (struct forma*) malloc(sizeof(struct forma));
    f->id = id;
    f->tipo = 'r';
    f->x = x;
    f->y = y;
    f->w = w;
    f->h = h;
    f->selecionada = 0;
    setFormaCorBorda(f, corb);
    setFormaCorPreenchimento(f, corp);
    return (Figura)f;
}

Figura criaLinhaStruct(int id, double x1, double y1, double x2, double y2, char* corb) {
    struct forma *f = (struct forma*) malloc(sizeof(struct forma));
    f->id = id;
    f->tipo = 'l';
    f->x = x1;
    f->y = y1;
    f->x2 = x2;
    f->y2 = y2;
    f->selecionada = 0;
    setFormaCorBorda(f, corb);
    return (Figura)f;
}

Figura criaTextoStruct(int id, double x, double y, char* corb, char* corp, char ancora, char* texto) {
    struct forma *f = (struct forma*) malloc(sizeof(struct forma));
    f->id = id;
    f->tipo = 't';
    f->x = x;
    f->y = y;
    f->ancora = ancora;
    f->selecionada = 0;
    setFormaCorBorda(f, corb);
    setFormaCorPreenchimento(f, corp);
    memset(f->texto, 0, sizeof(f->texto));
    strncpy(f->texto, texto, sizeof(f->texto) - 1);
    f->texto[sizeof(f->texto) - 1] = '\0';
    return (Figura)f;
}

void getAncoraFigura(Figura figura, double *x, double *y) {
    struct forma *f = (struct forma*) figura;
    if (f == NULL) return;

    switch (f->tipo) {
        case 'l': 
            if (f->x < f->x2) {
                *x = f->x;
                *y = f->y;
            } else if (f->x2 < f->x) {
                *x = f->x2;
                *y = f->y2;
            } else { 
                if (f->y <= f->y2) {
                    *x = f->x;
                    *y = f->y;
                } else {
                    *x = f->x2;
                    *y = f->y2;
                }
            }
            break;

        case 'c':
        case 'r':
        case 't':
        default:
            *x = f->x;
            *y = f->y;
            break;
    }
}

int isFiguraSelecionada(void* fig) {
    return ((struct forma*)fig)->selecionada;
}

void setFiguraSelecionada(void* fig, int sel) {
    ((struct forma*)fig)->selecionada = sel;
}

void liberaFigura(void* fig) {
    if (fig != NULL) {
        free(fig);
    }
}

void* clonaFigura(void* figuraOriginal) {
    struct forma* orig = (struct forma*) figuraOriginal;
    if (orig == NULL) return NULL;
    
    struct forma* clone = malloc(sizeof(struct forma));
    if (clone != NULL) {
        memcpy(clone, orig, sizeof(struct forma));
    }
    return (void*) clone;
}

void setCorPreenchimento(void* fig, char* cor) {
    if (cor != NULL) {
        memset(((struct forma*)fig)->corp, 0, 30);
        strncpy(((struct forma*)fig)->corp, cor, 29);
        ((struct forma*)fig)->corp[29] = '\0'; 
    }
}

int estaDentroDaRegiao(void* fig, double rx, double ry, double rw, double rh) {
    struct forma* f = (struct forma*) fig;
    if (f == NULL) return 0;

    double rx_max = rx + rw;
    double ry_max = ry + rh;

    switch (f->tipo) {
        case 'c': {
            return (f->x >= rx && f->x <= rx_max && f->y >= ry && f->y <= ry_max);
        }
        case 'r': {
            double fr_max_x = f->x + f->w;
            double fr_max_y = f->y + f->h;
            return (f->x >= rx && fr_max_x <= rx_max && f->y >= ry && fr_max_y <= ry_max);
        }
        case 'l': { 
            int p1_dentro = (f->x >= rx && f->x <= rx_max && f->y >= ry && f->y <= ry_max);
            int p2_dentro = (f->x2 >= rx && f->x2 <= rx_max && f->y2 >= ry && f->y2 <= ry_max);
            return (p1_dentro && p2_dentro);
        }
        case 't': { 
            return (f->x >= rx && f->x <= rx_max && f->y >= ry && f->y <= ry_max);
        }
        default:
            return 0;
    }
}

int comparaFiguras(void* f1, void* f2, char* criterio) {
    if (f1 == NULL || f2 == NULL) return 0;

    if (strcmp(criterio, "a") == 0) {
        double a1 = (getFormaTipo(f1) == 'r') ? (getFormaW(f1) * getFormaH(f1)) : (3.14159 * getFormaR(f1) * getFormaR(f1));
        double a2 = (getFormaTipo(f2) == 'r') ? (getFormaW(f2) * getFormaH(f2)) : (3.14159 * getFormaR(f2) * getFormaR(f2));
        return (a1 > a2) - (a1 < a2);
    }
    if (strcmp(criterio, "w") == 0) { 
        return (getFormaW(f1) > getFormaW(f2)) - (getFormaW(f1) < getFormaW(f2));
    }
    if (strcmp(criterio, "h") == 0) { 
        return (getFormaH(f1) > getFormaH(f2)) - (getFormaH(f1) < getFormaH(f2));
    }
    if (strcmp(criterio, "c") == 0) {
        return strcmp(getFormaCorPreenchimento(f1), getFormaCorPreenchimento(f2));
    }
    
    return (getFormaId(f1) > getFormaId(f2)) - (getFormaId(f1) < getFormaId(f2));
}
