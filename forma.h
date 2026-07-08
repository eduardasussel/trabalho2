#ifndef FORMA_H
#define FORMA_H

typedef void* Figura;

Figura criaCirculoStruct(int id, double x, double y, double r, char* corb, char* corp);
Figura criaRetanguloStruct(int id, double x, double y, double w, double h, char* corb, char* corp);
Figura criaLinhaStruct(int id, double x1, double y1, double x2, double y2, char* corb);
Figura criaTextoStruct(int id, double x, double y, char* corb, char* corp, char ancora, char* texto);

double getFormaX1(void* fig);
double getFormaY1(void* fig);
double getFormaX2(void* fig);
double getFormaY2(void* fig);
double getFormaW(void* fig);
double getFormaH(void* fig);
double getFormaR(void* fig);
char getFormaTipo(void* fig);
int getFormaId(void* fig);
char* getFormaCorPreenchimento(void* fig);
char* getFormaCorBorda(void* fig);
char* getFormaTexto(Figura f);
char getFormaAncora(Figura f);
double getFormaY(void* fig);

void setFormaX1(void* fig, double x);
void setFormaY1(void* fig, double y);
void setFormaX2(void* fig, double x2);
void setFormaY2(void* fig, double y2);
void setFormaCorBorda(void* fig, char* cor);
void setFormaCorPreenchimento(void* fig, char* cor);
void setAncoraFigura(void* fig, double x, double y);

int isFiguraSelecionada(void* fig);
void setFiguraSelecionada(void* fig, int sel);
void* clonaFigura(void* figuraOriginal);
void liberaFigura(void* fig);

int estaDentroDaRegiao(void* fig, double rx, double ry, double rw, double rh);
void getAncoraFigura(Figura figura, double *x, double *y);
int comparaFiguras(void* f1, void* f2, char* criterio);

#endif