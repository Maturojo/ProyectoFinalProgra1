#include <stdio.h>
#include <stdlib.h>
#include "contenidos.h"
#include "datos_prueba.h"
#include "estructuras.h"
#include "generos.h"
#include "usuarios.h"
#include "utils.h"
#include "visualizaciones.h"

void mostrarMenuPrincipal();
void menuAdministrador(Usuario usuario);
void menuUsuarioComun(Usuario usuario);

int main()
{
    int opcion;
    Usuario usuarioLogueado;


    configurarColorConsola();
    inicializarUsuarios();

    do
    {
        mostrarMenuPrincipal();
        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 2);

        switch (opcion)
        {
            case 1:
                if (loginUsuario(&usuarioLogueado))
                {
                    if (usuarioLogueado.rol == ROL_ADMIN)
                    {
                        menuAdministrador(usuarioLogueado);
                    }
                    else
                    {
                        menuUsuarioComun(usuarioLogueado);
                    }
                }
                break;

            case 2:
                registrarUsuario();
                break;

            case 0:
                mostrarMensajeExito("\nSaliendo del sistema...\n");
                break;
        }
    }
    while (opcion != 0);

    return 0;
}

void mostrarMenuPrincipal()
{
    system("cls");
    printf("========================================\n");
    printf("   Plataforma de Streaming - Etapa 6\n");
    printf("========================================\n");
    printf("1. Iniciar sesion\n");
    printf("2. Registrarse\n");
    printf("0. Salir\n");
    printf("----------------------------------------\n");
}

void menuAdministrador(Usuario usuario)
{
    int opcion;

    do
    {
        system("cls");
        printf("========================================\n");
        printf("           Menu administrador\n");
        printf("========================================\n");
        printf("Usuario: %s\n", usuario.nombre);
        printf("Usuario activo: %d\n", contarUsuarioActivos());
        printf("----------------------------------------\n");
        printf("1. Administrar generos\n");
        printf("2. Administrar contenidos\n");
        printf("3. Administrar usuarios\n");
        printf("4. Reporte de visualizaciones\n");
        printf("5. Cargar datos de prueba\n");
        printf("0. Cerrar sesion\n");
        printf("----------------------------------------\n");

        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 5);

        switch (opcion)
        {
            case 1:
                menuGeneros();
                break;

            case 2:
                menuContenidos();
                break;

            case 3:
                menuUsuarios();
                break;

            case 4:
                listarTodasVisualizaciones();
                pausar();
                break;

            case 5:
                cargarDatosPrueba();
                break;

            case 0:
                mostrarMensajeExito("\nSesion cerrada.\n");
                pausar();
                break;
        }
    }
    while (opcion != 0);
}

void menuUsuarioComun(Usuario usuario)
{
    int opcion;

    do
    {
        system("cls");
        printf("========================================\n");
        printf("              Menu usuario\n");
        printf("========================================\n");
        printf("Usuario: %s\n", usuario.nombre);
        printf("----------------------------------------\n");
        printf("1. Ver catalogo\n");
        printf("2. Buscar contenido\n");
        printf("3. Registrar visualizacion\n");
        printf("4. Mis visualizaciones\n");
        printf("0. Cerrar sesion\n");
        printf("----------------------------------------\n");

        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 4);

        switch (opcion)
        {
            case 1:
                listarContenidos();
                pausar();
                break;

            case 2:
                buscarContenidosPorTitulo();
                break;

            case 3:
                registrarVisualizacion(usuario);
                break;

            case 4:
                listarVisualizacionesUsuario(usuario.id);
                pausar();
                break;

            case 0:
                mostrarMensajeExito("\nSesion cerrada.\n");
                pausar();
                break;
        }
    }
    while (opcion != 0);
}
