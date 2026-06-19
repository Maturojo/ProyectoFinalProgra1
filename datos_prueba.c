#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contenidos.h"
#include "datos_prueba.h"
#include "generos.h"
#include "usuarios.h"
#include "utils.h"
#include "visualizaciones.h"

int archivoTieneRegistros(const char nombreArchivo[], int tamanioRegistro);
void cargarGenerosPrueba(void);
void cargarUsuariosPrueba(void);
void cargarContenidosPrueba(void);
void cargarVisualizacionesPrueba(void);

void cargarDatosPrueba(void)
{
    system("cls");
    printf("========================================\n");
    printf("          Carga de datos de prueba\n");
    printf("========================================\n");

    cargarGenerosPrueba();
    cargarUsuariosPrueba();
    cargarContenidosPrueba();
    cargarVisualizacionesPrueba();

    mostrarMensajeExito("\nDatos de prueba cargados correctamente.\n");
    pausar();
}

int archivoTieneRegistros(const char nombreArchivo[], int tamanioRegistro)
{
    FILE *archivo;
    long tamanio;

    archivo = fopen(nombreArchivo, "rb");

    if (archivo == NULL)
    {
        return 0;
    }

    fseek(archivo, 0, SEEK_END);
    tamanio = ftell(archivo);
    fclose(archivo);

    return tamanio >= tamanioRegistro;
}

void cargarGenerosPrueba(void)
{
    FILE *archivo;
    Genero generos[4] = {
        {1, "Accion", 1},
        {2, "Comedia", 1},
        {3, "Drama", 1},
        {4, "Ciencia ficcion", 1}
    };

    if (archivoTieneRegistros(ARCHIVO_GENEROS, sizeof(Genero)))
    {
        printf("Generos: ya existen datos, no se duplican.\n");
        return;
    }

    archivo = fopen(ARCHIVO_GENEROS, "wb");

    if (archivo == NULL)
    {
        mostrarMensajeError("No se pudo cargar generos de prueba.\n");
        return;
    }

    fwrite(generos, sizeof(Genero), 4, archivo);
    fclose(archivo);
    printf("Generos: cargados.\n");
}

void cargarUsuariosPrueba(void)
{
    FILE *archivo;
    Usuario usuario;

    if (existeUsuarioActivoConEmail("usuario1@mail.com") || existeUsuarioActivoConEmail("usuario2@mail.com"))
    {
        printf("Usuarios: ya existen datos de prueba, no se duplican.\n");
        return;
    }

    archivo = fopen(ARCHIVO_USUARIOS, "ab");

    if (archivo == NULL)
    {
        mostrarMensajeError("No se pudo cargar usuarios de prueba.\n");
        return;
    }

    usuario.id = obtenerSiguienteIdUsuario();
    strcpy(usuario.nombre, "Usuario Uno");
    strcpy(usuario.email, "usuario1@mail.com");
    strcpy(usuario.password, "1234");
    usuario.rol = ROL_USUARIO;
    usuario.activo = 1;
    fwrite(&usuario, sizeof(Usuario), 1, archivo);

    usuario.id = usuario.id + 1;
    strcpy(usuario.nombre, "Usuario Dos");
    strcpy(usuario.email, "usuario2@mail.com");
    strcpy(usuario.password, "1234");
    usuario.rol = ROL_USUARIO;
    usuario.activo = 1;
    fwrite(&usuario, sizeof(Usuario), 1, archivo);

    fclose(archivo);
    printf("Usuarios: cargados.\n");
}

void cargarContenidosPrueba(void)
{
    FILE *archivo;
    Contenido contenidos[3] = {
        {1, "Matrix", "Un hacker descubre la verdad sobre su mundo.", 4, 1999, 136, TIPO_PELICULA, 1},
        {2, "Friends", "Un grupo de amigos vive situaciones comicas.", 2, 1994, 25, TIPO_SERIE, 1},
        {3, "Gladiador", "Un general romano busca justicia.", 3, 2000, 155, TIPO_PELICULA, 1}
    };

    if (archivoTieneRegistros(ARCHIVO_CONTENIDOS, sizeof(Contenido)))
    {
        printf("Contenidos: ya existen datos, no se duplican.\n");
        return;
    }

    archivo = fopen(ARCHIVO_CONTENIDOS, "wb");

    if (archivo == NULL)
    {
        mostrarMensajeError("No se pudo cargar contenidos de prueba.\n");
        return;
    }

    fwrite(contenidos, sizeof(Contenido), 3, archivo);
    fclose(archivo);
    printf("Contenidos: cargados.\n");
}

void cargarVisualizacionesPrueba(void)
{
    FILE *archivo;
    Visualizacion visualizaciones[3] = {
        {1, 2, 1, "19/06/2026", 80, 1},
        {2, 2, 2, "19/06/2026", 25, 1},
        {3, 3, 3, "19/06/2026", 120, 1}
    };

    if (archivoTieneRegistros(ARCHIVO_VISUALIZACIONES, sizeof(Visualizacion)))
    {
        printf("Visualizaciones: ya existen datos, no se duplican.\n");
        return;
    }

    archivo = fopen(ARCHIVO_VISUALIZACIONES, "wb");

    if (archivo == NULL)
    {
        mostrarMensajeError("No se pudo cargar visualizaciones de prueba.\n");
        return;
    }

    fwrite(visualizaciones, sizeof(Visualizacion), 3, archivo);
    fclose(archivo);
    printf("Visualizaciones: cargadas.\n");
}
