#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#define TAM_NOMBRE 50
#define TAM_EMAIL 80
#define TAM_PASSWORD 30
#define TAM_TITULO 80
#define TAM_DESCRIPCION 200
#define TAM_FECHA 11

typedef struct
{
    int id;
    char nombre[TAM_NOMBRE];
    int activo;
} Genero;

typedef struct
{
    int id;
    char nombre[TAM_NOMBRE];
    char email[TAM_EMAIL];
    char password[TAM_PASSWORD];
    int rol; /* 1 = administrador, 2 = usuario comun */
    int activo;
} Usuario;

typedef struct
{
    int id;
    char titulo[TAM_TITULO];
    char descripcion[TAM_DESCRIPCION];
    int idGenero;
    int anio;
    int duracionMinutos;
    int tipo; /* 1 = pelicula, 2 = serie */
    int activo;
} Contenido;

typedef struct
{
    int id;
    int idUsuario;
    int idContenido;
    char fecha[TAM_FECHA]; /* formato sugerido: dd/mm/aaaa */
    int minutosVistos;
    int activo;
} Visualizacion;

#endif
