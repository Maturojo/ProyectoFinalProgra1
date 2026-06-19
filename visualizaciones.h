#ifndef VISUALIZACIONES_H_INCLUDED
#define VISUALIZACIONES_H_INCLUDED

#include "estructuras.h"

#define ARCHIVO_VISUALIZACIONES "visualizaciones.dat"

void registrarVisualizacion(Usuario usuario);
void listarVisualizacionesUsuario(int idUsuario);
void listarTodasVisualizaciones(void);

int obtenerSiguienteIdVisualizacion(void);
void mostrarVisualizacion(Visualizacion visualizacion);

#endif
