#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contenidos.h"
#include "utils.h"
#include "visualizaciones.h"

void registrarVisualizacion(Usuario usuario)
{
    FILE *archivo;
    Visualizacion visualizacion;
    Contenido contenido;

    system("cls");
    printf("========================================\n");
    printf("        Registrar visualizacion\n");
    printf("========================================\n");

    listarContenidos();
    visualizacion.idContenido = leerEntero("\nIngrese el ID del contenido visto: ");

    if (!buscarContenidoPorId(visualizacion.idContenido, &contenido, NULL))
    {
        printf("\nNo existe un contenido activo con ese ID.\n");
        pausar();
        return;
    }

    printf("Fecha (dd/mm/aaaa): ");
    leerCadena(visualizacion.fecha, TAM_FECHA);

    if (strlen(visualizacion.fecha) == 0)
    {
        printf("\nLa fecha es obligatoria.\n");
        pausar();
        return;
    }

    visualizacion.minutosVistos = leerEnteroRango("Minutos vistos: ", 1, contenido.duracionMinutos);
    visualizacion.id = obtenerSiguienteIdVisualizacion();
    visualizacion.idUsuario = usuario.id;
    visualizacion.activo = 1;

    archivo = fopen(ARCHIVO_VISUALIZACIONES, "ab");

    if (archivo == NULL)
    {
        printf("\nNo se pudo abrir el archivo de visualizaciones.\n");
        pausar();
        return;
    }

    fwrite(&visualizacion, sizeof(Visualizacion), 1, archivo);
    fclose(archivo);

    printf("\nVisualizacion registrada correctamente.\n");
    pausar();
}

void listarVisualizacionesUsuario(int idUsuario)
{
    FILE *archivo;
    Visualizacion visualizacion;
    int encontrados = 0;

    system("cls");
    printf("========================================\n");
    printf("           Mis visualizaciones\n");
    printf("========================================\n");

    archivo = fopen(ARCHIVO_VISUALIZACIONES, "rb");

    if (archivo == NULL)
    {
        printf("No hay visualizaciones registradas.\n");
        return;
    }

    while (fread(&visualizacion, sizeof(Visualizacion), 1, archivo) == 1)
    {
        if (visualizacion.activo && visualizacion.idUsuario == idUsuario)
        {
            mostrarVisualizacion(visualizacion);
            encontrados = 1;
        }
    }

    fclose(archivo);

    if (!encontrados)
    {
        printf("No tenes visualizaciones registradas.\n");
    }
}

int obtenerSiguienteIdVisualizacion(void)
{
    FILE *archivo;
    Visualizacion visualizacion;
    int mayorId = 0;

    archivo = fopen(ARCHIVO_VISUALIZACIONES, "rb");

    if (archivo == NULL)
    {
        return 1;
    }

    while (fread(&visualizacion, sizeof(Visualizacion), 1, archivo) == 1)
    {
        if (visualizacion.id > mayorId)
        {
            mayorId = visualizacion.id;
        }
    }

    fclose(archivo);

    return mayorId + 1;
}

void mostrarVisualizacion(Visualizacion visualizacion)
{
    Contenido contenido;

    if (buscarContenidoPorId(visualizacion.idContenido, &contenido, NULL))
    {
        printf("ID: %d | Contenido: %s | Fecha: %s | Minutos vistos: %d\n",
               visualizacion.id,
               contenido.titulo,
               visualizacion.fecha,
               visualizacion.minutosVistos);
    }
    else
    {
        printf("ID: %d | Contenido dado de baja | Fecha: %s | Minutos vistos: %d\n",
               visualizacion.id,
               visualizacion.fecha,
               visualizacion.minutosVistos);
    }
}
