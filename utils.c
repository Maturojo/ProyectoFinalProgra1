#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "color.h"
#include "utils.h"

void limpiarBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void configurarColorConsola(void)
{
    colorNormal();
}

void colorNormal(void)
{
    color(11);
}

void colorError(void)
{
    color(4);
}

void colorExito(void)
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

void pausar(void)
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
