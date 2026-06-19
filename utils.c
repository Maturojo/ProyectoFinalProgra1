#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "color.h"
#include "utils.h"

void limpiarBuffer()
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void configurarColorConsola()
{
    colorNormal();
}

void colorNormal()
{
    color(11);
}

void colorError()
{
    color(4);
}

void colorExito()
{
    color(10);
}

void mostrarMensajeError(const char mensaje[])
{
    colorError();
    printf("%s", mensaje);
    colorNormal();
}

void mostrarMensajeExito(const char mensaje[])
{
    colorExito();
    printf("%s", mensaje);
    colorNormal();
}

void pausar()
{
    printf("\nPresione ENTER para continuar...");
    getchar();
}

void leerCadena(char texto[], int tamanio)
{
    int longitud;

    fgets(texto, tamanio, stdin);
    longitud = strlen(texto);

    if (longitud > 0 && texto[longitud - 1] == '\n')
    {
        texto[longitud - 1] = '\0';
    }
    else
    {
        limpiarBuffer();
    }
}

void leerPassword(char password[], int tamanio)
{
    int i = 0;
    char tecla;

    do
    {
        tecla = getch();

        if (tecla == 13)
        {
            password[i] = '\0';
            printf("\n");
        }
        else if (tecla == 8)
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (i < tamanio - 1)
        {
            password[i] = tecla;
            i++;
            printf("*");
        }
    }
    while (tecla != 13);
}

int leerEntero(const char mensaje[])
{
    int valor;
    int resultado;

    do
    {
        printf("%s", mensaje);
        resultado = scanf("%d", &valor);
        limpiarBuffer();

        if (resultado != 1)
        {
            mostrarMensajeError("Dato invalido. Ingrese un numero entero.\n");
        }
    }
    while (resultado != 1);

    return valor;
}

int leerEnteroRango(const char mensaje[], int minimo, int maximo)
{
    int valor;

    do
    {
        valor = leerEntero(mensaje);

        if (valor < minimo || valor > maximo)
        {
            colorError();
            printf("Opcion invalida. Ingrese un valor entre %d y %d.\n", minimo, maximo);
            colorNormal();
        }
    }
    while (valor < minimo || valor > maximo);

    return valor;
}

int confirmar(const char mensaje[])
{
    char opcion;

    do
    {
        printf("%s (s/n): ", mensaje);
        scanf(" %c", &opcion);
        limpiarBuffer();

        if (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N')
        {
            mostrarMensajeError("Respuesta invalida. Ingrese s o n.\n");
        }
    }
    while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N');

    return opcion == 's' || opcion == 'S';
}

int validarEmail(const char email[])
{
    int i;
    int tieneArroba = 0;
    int tienePunto = 0;

    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            tieneArroba = 1;
        }
        if (email[i] == '.')
        {
            tienePunto = 1;
        }
    }

    return tieneArroba && tienePunto;
}

int validarFecha(const char fecha[])
{
    int i;

    if (strlen(fecha) != 10)
    {
        return 0;
    }

    if (fecha[2] != '/' || fecha[5] != '/')
    {
        return 0;
    }

    for (i = 0; i < 10; i++)
    {
        if (i != 2 && i != 5 && (fecha[i] < '0' || fecha[i] > '9'))
        {
            return 0;
        }
    }

    return 1;
}
