#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contenidos.h"
#include "generos.h"
#include "utils.h"

void menuContenidos(void)
{
    int opcion;

    do
    {
        system("cls");
        printf("========================================\n");
        printf("            Gestion de contenidos\n");
        printf("========================================\n");
        printf("1. Alta de contenido\n");
        printf("2. Listar contenidos\n");
        printf("3. Modificar contenido\n");
        printf("4. Baja de contenido\n");
        printf("0. Volver\n");
        printf("----------------------------------------\n");

        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 4);

        switch (opcion)
        {
            case 1:
                altaContenido();
                break;

            case 2:
                listarContenidos();
                pausar();
                break;

            case 3:
                modificarContenido();
                break;

            case 4:
                bajaContenido();
                break;
        }
    }
    while (opcion != 0);
}

void altaContenido(void)
{
    FILE *archivo;
    Contenido contenido;
    Genero genero;

    system("cls");
    printf("========================================\n");
    printf("            Alta de contenido\n");
    printf("========================================\n");

    printf("Titulo: ");
    leerCadena(contenido.titulo, TAM_TITULO);

    printf("Descripcion: ");
    leerCadena(contenido.descripcion, TAM_DESCRIPCION);

    contenido.anio = leerEnteroRango("Anio: ", 1900, 2100);
    contenido.duracionMinutos = leerEnteroRango("Duracion en minutos: ", 1, 1000);
    contenido.tipo = leerEnteroRango("Tipo (1 pelicula, 2 serie): ", 1, 2);

    listarGeneros();
    contenido.idGenero = leerEntero("\nID de genero: ");

    if (!buscarGeneroPorId(contenido.idGenero, &genero, NULL))
    {
        mostrarMensajeError("\nNo existe un genero activo con ese ID.\n");
        pausar();
        return;
    }

    if (strlen(contenido.titulo) == 0 || strlen(contenido.descripcion) == 0)
    {
        mostrarMensajeError("\nTitulo y descripcion son obligatorios.\n");
        pausar();
        return;
    }

    contenido.id = obtenerSiguienteIdContenido();
    contenido.activo = 1;

    archivo = fopen(ARCHIVO_CONTENIDOS, "ab");

    if (archivo == NULL)
    {
        mostrarMensajeError("\nNo se pudo abrir el archivo de contenidos.\n");
        pausar();
        return;
    }

    fwrite(&contenido, sizeof(Contenido), 1, archivo);
    fclose(archivo);

    colorExito();
    printf("\nContenido guardado correctamente con ID %d.\n", contenido.id);
    colorNormal();
    pausar();
}

void listarContenidos(void)
{
    FILE *archivo;
    Contenido contenido;
    int encontrados = 0;

    system("cls");
    printf("========================================\n");
    printf("           Listado de contenidos\n");
    printf("========================================\n");

    archivo = fopen(ARCHIVO_CONTENIDOS, "rb");

    if (archivo == NULL)
    {
        printf("No hay contenidos cargados.\n");
        return;
    }

    while (fread(&contenido, sizeof(Contenido), 1, archivo) == 1)
    {
        if (contenido.activo)
        {
            mostrarContenido(contenido);
            encontrados = 1;
        }
    }

    fclose(archivo);

    if (!encontrados)
    {
        printf("No hay contenidos activos.\n");
    }
}

void modificarContenido(void)
{
    FILE *archivo;
    Contenido contenido;
    Genero genero;
    int id;
    long posicion;

    listarContenidos();
    id = leerEntero("\nIngrese el ID del contenido a modificar: ");

    if (!buscarContenidoPorId(id, &contenido, &posicion))
    {
        mostrarMensajeError("\nNo se encontro un contenido activo con ese ID.\n");
        pausar();
        return;
    }

    printf("Nuevo titulo: ");
    leerCadena(contenido.titulo, TAM_TITULO);

    printf("Nueva descripcion: ");
    leerCadena(contenido.descripcion, TAM_DESCRIPCION);

    contenido.anio = leerEnteroRango("Nuevo anio: ", 1900, 2100);
    contenido.duracionMinutos = leerEnteroRango("Nueva duracion en minutos: ", 1, 1000);
    contenido.tipo = leerEnteroRango("Nuevo tipo (1 pelicula, 2 serie): ", 1, 2);

    listarGeneros();
    contenido.idGenero = leerEntero("\nNuevo ID de genero: ");

    if (!buscarGeneroPorId(contenido.idGenero, &genero, NULL))
    {
        mostrarMensajeError("\nNo existe un genero activo con ese ID.\n");
        pausar();
        return;
    }

    if (strlen(contenido.titulo) == 0 || strlen(contenido.descripcion) == 0)
    {
        mostrarMensajeError("\nTitulo y descripcion son obligatorios.\n");
        pausar();
        return;
    }

    archivo = fopen(ARCHIVO_CONTENIDOS, "r+b");

    if (archivo == NULL)
    {
        mostrarMensajeError("\nNo se pudo abrir el archivo de contenidos.\n");
        pausar();
        return;
    }

    fseek(archivo, posicion, SEEK_SET);
    fwrite(&contenido, sizeof(Contenido), 1, archivo);
    fclose(archivo);

    mostrarMensajeExito("\nContenido modificado correctamente.\n");
    pausar();
}

void bajaContenido(void)
{
    FILE *archivo;
    Contenido contenido;
    int id;
    long posicion;

    listarContenidos();
    id = leerEntero("\nIngrese el ID del contenido a dar de baja: ");

    if (!buscarContenidoPorId(id, &contenido, &posicion))
    {
        mostrarMensajeError("\nNo se encontro un contenido activo con ese ID.\n");
        pausar();
        return;
    }

    if (!confirmar("Confirma la baja del contenido"))
    {
        mostrarMensajeError("\nOperacion cancelada.\n");
        pausar();
        return;
    }

    contenido.activo = 0;

    archivo = fopen(ARCHIVO_CONTENIDOS, "r+b");

    if (archivo == NULL)
    {
        mostrarMensajeError("\nNo se pudo abrir el archivo de contenidos.\n");
        pausar();
        return;
    }

    fseek(archivo, posicion, SEEK_SET);
    fwrite(&contenido, sizeof(Contenido), 1, archivo);
    fclose(archivo);

    mostrarMensajeExito("\nContenido dado de baja correctamente.\n");
    pausar();
}

int obtenerSiguienteIdContenido(void)
{
    FILE *archivo;
    Contenido contenido;
    int mayorId = 0;

    archivo = fopen(ARCHIVO_CONTENIDOS, "rb");

    if (archivo == NULL)
    {
        return 1;
    }

    while (fread(&contenido, sizeof(Contenido), 1, archivo) == 1)
    {
        if (contenido.id > mayorId)
        {
            mayorId = contenido.id;
        }
    }

    fclose(archivo);

    return mayorId + 1;
}

int buscarContenidoPorId(int id, Contenido *contenido, long *posicion)
{
    FILE *archivo;
    Contenido aux;
    long posActual;

    archivo = fopen(ARCHIVO_CONTENIDOS, "rb");

    if (archivo == NULL)
    {
        return 0;
    }

    while (fread(&aux, sizeof(Contenido), 1, archivo) == 1)
    {
        posActual = ftell(archivo) - sizeof(Contenido);

        if (aux.id == id && aux.activo)
        {
            if (contenido != NULL)
            {
                *contenido = aux;
            }

            if (posicion != NULL)
            {
                *posicion = posActual;
            }

            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

void mostrarContenido(Contenido contenido)
{
    printf("ID: %d | Titulo: %s | Anio: %d | Duracion: %d min | Tipo: %s | ID genero: %d\n",
           contenido.id,
           contenido.titulo,
           contenido.anio,
           contenido.duracionMinutos,
           contenido.tipo == TIPO_PELICULA ? "Pelicula" : "Serie",
           contenido.idGenero);
}
