#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"
#include "generos.h"
#include "utils.h"

void mostrarMenuPrincipal(void);

int main()
{
    int opcion;

    configurarColorConsola();

    do
    {
        mostrarMenuPrincipal();
        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 3);

        switch (opcion)
        {
            case 1:
                printf("\nModulo de login pendiente para proximas etapas.\n");
                pausar();
                break;

            case 2:
                printf("\nRegistro de usuarios pendiente para proximas etapas.\n");
                pausar();
                break;

            case 3:
                menuGeneros();
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
    printf("   Plataforma de Streaming - Etapa 2\n");
    printf("========================================\n");
    printf("1. Iniciar sesion\n");
    printf("2. Registrarse\n");
    printf("3. Administrar generos\n");
    printf("0. Salir\n");
    printf("----------------------------------------\n");
}
