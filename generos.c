#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generos.h"
#include "utils.h"

void menuGeneros(void)
{
    int opcion;

    do
    {
        system("cls");
        printf("========================================\n");
        printf("             Gestion de generos\n");
        printf("========================================\n");
        printf("1. Alta de genero\n");
        printf("2. Listar generos\n");
        printf("3. Modificar genero\n");
        printf("4. Baja de genero\n");
        printf("0. Volver\n");
        printf("----------------------------------------\n");

        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 4);

        switch (opcion)
        {
            case 1:
                altaGenero();
                break;

            case 2:
                listarGeneros();
                pausar();
                break;

            case 3:
                modificarGenero();
                break;

            case 4:
                bajaGenero();
                break;
        }
    }
    while (opcion != 0);
}

void altaGenero(void)
{
    FILE *archivo;
    Genero genero;

    system("cls");
    printf("========================================\n");
    printf("              Alta de genero\n");
    printf("========================================\n");

    printf("Nombre: ");
    leerCadena(genero.nombre, TAM_NOMBRE);

    if (strlen(genero.nombre) == 0)
    {
        printf("\nEl nombre no puede estar vacio.\n");
        pausar();
        return;
    }

    if (existeGeneroActivoConNombre(genero.nombre))
    {
        printf("\nYa existe un genero activo con ese nombre.\n");
        pausar();
        return;
    }

    genero.id = obtenerSiguienteIdGenero();
    genero.activo = 1;

    archivo = fopen(ARCHIVO_GENEROS, "ab");

    if (archivo == NULL)
    {
        printf("\nNo se pudo abrir el archivo de generos.\n");
        pausar();
        return;
    }

    fwrite(&genero, sizeof(Genero), 1, archivo);
    fclose(archivo);

    printf("\nGenero guardado correctamente con ID %d.\n", genero.id);
    pausar();
}

void listarGeneros(void)
{
    FILE *archivo;
    Genero genero;
    int encontrados = 0;

    system("cls");
    printf("========================================\n");
    printf("             Listado de generos\n");
    printf("========================================\n");

    archivo = fopen(ARCHIVO_GENEROS, "rb");

    if (archivo == NULL)
    {
        printf("No hay generos cargados.\n");
        return;
    }

    while (fread(&genero, sizeof(Genero), 1, archivo) == 1)
    {
        if (genero.activo)
        {
            mostrarGenero(genero);
            encontrados = 1;
        }
    }

    fclose(archivo);

    if (!encontrados)
    {
        printf("No hay generos activos.\n");
    }
}

void modificarGenero(void)
{
    FILE *archivo;
    Genero genero;
    int id;
    long posicion;
    char nuevoNombre[TAM_NOMBRE];

    listarGeneros();
    id = leerEntero("\nIngrese el ID del genero a modificar: ");

    if (!buscarGeneroPorId(id, &genero, &posicion))
    {
        printf("\nNo se encontro un genero activo con ese ID.\n");
        pausar();
        return;
    }

    printf("Nuevo nombre: ");
    leerCadena(nuevoNombre, TAM_NOMBRE);

    if (strlen(nuevoNombre) == 0)
    {
        printf("\nEl nombre no puede estar vacio.\n");
        pausar();
        return;
    }

    if (strcmp(genero.nombre, nuevoNombre) != 0 && existeGeneroActivoConNombre(nuevoNombre))
    {
        printf("\nYa existe un genero activo con ese nombre.\n");
        pausar();
        return;
    }

    strcpy(genero.nombre, nuevoNombre);

    archivo = fopen(ARCHIVO_GENEROS, "r+b");

    if (archivo == NULL)
    {
        printf("\nNo se pudo abrir el archivo de generos.\n");
        pausar();
        return;
    }

    fseek(archivo, posicion, SEEK_SET);
    fwrite(&genero, sizeof(Genero), 1, archivo);
    fclose(archivo);

    printf("\nGenero modificado correctamente.\n");
    pausar();
}

void bajaGenero(void)
{
    FILE *archivo;
    Genero genero;
    int id;
    long posicion;

    listarGeneros();
    id = leerEntero("\nIngrese el ID del genero a dar de baja: ");

    if (!buscarGeneroPorId(id, &genero, &posicion))
    {
        printf("\nNo se encontro un genero activo con ese ID.\n");
        pausar();
        return;
    }

    if (!confirmar("Confirma la baja del genero"))
    {
        printf("\nOperacion cancelada.\n");
        pausar();
        return;
    }

    genero.activo = 0;

    archivo = fopen(ARCHIVO_GENEROS, "r+b");

    if (archivo == NULL)
    {
        printf("\nNo se pudo abrir el archivo de generos.\n");
        pausar();
        return;
    }

    fseek(archivo, posicion, SEEK_SET);
    fwrite(&genero, sizeof(Genero), 1, archivo);
    fclose(archivo);

    printf("\nGenero dado de baja correctamente.\n");
    pausar();
}

int obtenerSiguienteIdGenero(void)
{
    FILE *archivo;
    Genero genero;
    int mayorId = 0;

    archivo = fopen(ARCHIVO_GENEROS, "rb");

    if (archivo == NULL)
    {
        return 1;
    }

    while (fread(&genero, sizeof(Genero), 1, archivo) == 1)
    {
        if (genero.id > mayorId)
        {
            mayorId = genero.id;
        }
    }

    fclose(archivo);

    return mayorId + 1;
}

int buscarGeneroPorId(int id, Genero *genero, long *posicion)
{
    FILE *archivo;
    Genero aux;
    long posActual;

    archivo = fopen(ARCHIVO_GENEROS, "rb");

    if (archivo == NULL)
    {
        return 0;
    }

    while (fread(&aux, sizeof(Genero), 1, archivo) == 1)
    {
        posActual = ftell(archivo) - sizeof(Genero);

        if (aux.id == id && aux.activo)
        {
            if (genero != NULL)
            {
                *genero = aux;
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

int existeGeneroActivoConNombre(const char nombre[])
{
    FILE *archivo;
    Genero genero;

    archivo = fopen(ARCHIVO_GENEROS, "rb");

    if (archivo == NULL)
    {
        return 0;
    }

    while (fread(&genero, sizeof(Genero), 1, archivo) == 1)
    {
        if (genero.activo && strcmp(genero.nombre, nombre) == 0)
        {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

void mostrarGenero(Genero genero)
{
    printf("ID: %d | Nombre: %s\n", genero.id, genero.nombre);
}
