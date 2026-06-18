#include <stdio.h>
#include <stdlib.h>
#include "contenidos.h"
#include "estructuras.h"
#include "generos.h"
#include "usuarios.h"
#include "utils.h"

void mostrarMenuPrincipal(void);
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
                printf("\nSaliendo del sistema...\n");
                break;
        }
    }
    while (opcion != 0);

    return 0;
}

void mostrarMenuPrincipal(void)
{
    system("cls");
    printf("========================================\n");
    printf("   Plataforma de Streaming - Etapa 3\n");
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
        printf("----------------------------------------\n");
        printf("1. Administrar generos\n");
        printf("2. Administrar contenidos\n");
        printf("0. Cerrar sesion\n");
        printf("----------------------------------------\n");

        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 2);

        switch (opcion)
        {
            case 1:
                menuGeneros();
                break;

            case 2:
                menuContenidos();
                break;

            case 0:
                printf("\nSesion cerrada.\n");
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
        printf("0. Cerrar sesion\n");
        printf("----------------------------------------\n");

        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 1);

        switch (opcion)
        {
            case 1:
                listarContenidos();
                pausar();
                break;

            case 0:
                printf("\nSesion cerrada.\n");
                pausar();
                break;
        }
    }
    while (opcion != 0);
}
