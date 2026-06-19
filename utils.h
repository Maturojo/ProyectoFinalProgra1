#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

void limpiarBuffer(void);
void configurarColorConsola(void);
void colorNormal(void);
void colorError(void);
void colorExito(void);
void mostrarMensajeError(const char mensaje[]);
void mostrarMensajeExito(const char mensaje[]);
void pausar(void);
void leerCadena(char texto[], int tamanio);
void leerPassword(char password[], int tamanio);
int leerEntero(const char mensaje[]);
int leerEnteroRango(const char mensaje[], int minimo, int maximo);
int confirmar(const char mensaje[]);

#endif
