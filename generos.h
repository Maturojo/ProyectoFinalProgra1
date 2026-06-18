#ifndef GENEROS_H_INCLUDED
#define GENEROS_H_INCLUDED

#include "estructuras.h"

#define ARCHIVO_GENEROS "generos.dat"

void menuGeneros(void);
void altaGenero(void);
void listarGeneros(void);
void modificarGenero(void);
void bajaGenero(void);

int obtenerSiguienteIdGenero(void);
int buscarGeneroPorId(int id, Genero *genero, long *posicion);
int existeGeneroActivoConNombre(const char nombre[]);
void mostrarGenero(Genero genero);

#endif
