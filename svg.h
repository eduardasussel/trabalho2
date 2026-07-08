#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "forma.h"

FILE* iniciaSVG(char *path);
void desenhaFiguraSVG(FILE *svg, Figura f);
void desenhaRetanguloSel(FILE *svg, double x, double y, double w, double h);
void desenhaXExclusao(FILE *svg, double x, double y);
void finalizaSVG(FILE *svg);
void fechaSVG(FILE *svg);

#endif