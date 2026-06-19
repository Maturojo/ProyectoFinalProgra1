#ifndef GENEROS_H_INCLUDED
#define GENEROS_H_INCLUDED

#include "estructuras.h"

#define ARCHIVO_GENEROS "generos.dat"

void menuGeneros();
void altaGenero();
void listarGeneros();
void modificarGenero();
void bajaGenero();

int obtenerSiguienteIdGenero();
int buscarGeneroPorId(int id, Genero *genero, long *posicion);
int existeGeneroActivoConNombre(const char nombre[]);
int esNombreGeneroValido(const char nombre[]);
void mostrarGenero(Genero genero);

#endif
