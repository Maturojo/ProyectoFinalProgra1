#ifndef CONTENIDOS_H_INCLUDED
#define CONTENIDOS_H_INCLUDED

#include "estructuras.h"

#define ARCHIVO_CONTENIDOS "contenido.dat"
#define TIPO_PELICULA 1
#define TIPO_SERIE 2

void menuContenidos();
void altaContenido();
void listarContenidos();
void buscarContenidosPorTitulo();
void modificarContenido();
void bajaContenido();

int obtenerSiguienteIdContenido();
int buscarContenidoPorId(int id, Contenido *contenido, long *posicion);
void mostrarContenido(Contenido contenido);

#endif
