#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"
#include "utils.h"

void inicializarUsuarios(void)
{
    FILE *archivo;
    Usuario admin;

    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo != NULL)
    {
        fclose(archivo);
        return;
    }

    archivo = fopen(ARCHIVO_USUARIOS, "wb");

    if (archivo == NULL)
    {
        mostrarMensajeError("\nNo se pudo crear el archivo de usuarios.\n");
        pausar();
        return;
    }

    admin.id = 1;
    strcpy(admin.nombre, "Administrador");
    strcpy(admin.email, "admin@admin.com");
    strcpy(admin.password, "admin");
    admin.rol = ROL_ADMIN;
    admin.activo = 1;

    fwrite(&admin, sizeof(Usuario), 1, archivo);
    fclose(archivo);
}

void menuUsuarios(void)
{
    int opcion;

    do
    {
        system("cls");
        printf("========================================\n");
        printf("             Gestion de usuarios\n");
        printf("========================================\n");
        printf("1. Listar usuarios\n");
        printf("2. Baja de usuario\n");
        printf("0. Volver\n");
        printf("----------------------------------------\n");

        opcion = leerEnteroRango("Ingrese una opcion: ", 0, 2);

        switch (opcion)
        {
            case 1:
                listarUsuarios();
                pausar();
                break;

            case 2:
                bajaUsuario();
                break;
        }
    }
    while (opcion != 0);
}

void registrarUsuario(void)
{
    FILE *archivo;
    Usuario usuario;

    system("cls");
    printf("========================================\n");
    printf("          Registro de usuario\n");
    printf("========================================\n");

    printf("Nombre: ");
    leerCadena(usuario.nombre, TAM_NOMBRE);

    printf("Email: ");
    leerCadena(usuario.email, TAM_EMAIL);

    printf("Password: ");
    leerPassword(usuario.password, TAM_PASSWORD);

    if (strlen(usuario.nombre) == 0 || strlen(usuario.email) == 0 || strlen(usuario.password) == 0)
    {
        mostrarMensajeError("\nTodos los campos son obligatorios.\n");
        pausar();
        return;
    }

    if (existeUsuarioActivoConEmail(usuario.email))
    {
        mostrarMensajeError("\nYa existe un usuario activo con ese email.\n");
        pausar();
        return;
    }

    usuario.id = obtenerSiguienteIdUsuario();
    usuario.rol = ROL_USUARIO;
    usuario.activo = 1;

    archivo = fopen(ARCHIVO_USUARIOS, "ab");

    if (archivo == NULL)
    {
        mostrarMensajeError("\nNo se pudo abrir el archivo de usuarios.\n");
        pausar();
        return;
    }

    fwrite(&usuario, sizeof(Usuario), 1, archivo);
    fclose(archivo);

    mostrarMensajeExito("\nUsuario registrado correctamente.\n");
    pausar();
}

int loginUsuario(Usuario *usuarioLogueado)
{
    char email[TAM_EMAIL];
    char password[TAM_PASSWORD];

    system("cls");
    printf("========================================\n");
    printf("              Iniciar sesion\n");
    printf("========================================\n");

    printf("Email: ");
    leerCadena(email, TAM_EMAIL);

    printf("Password: ");
    leerPassword(password, TAM_PASSWORD);

    if (buscarUsuarioPorLogin(email, password, usuarioLogueado))
    {
        colorExito();
        printf("\nBienvenido/a, %s.\n", usuarioLogueado->nombre);
        colorNormal();
        pausar();
        return 1;
    }

    mostrarMensajeError("\nEmail o password incorrectos.\n");
    pausar();
    return 0;
}

void listarUsuarios(void)
{
    FILE *archivo;
    Usuario usuario;
    int encontrados = 0;

    system("cls");
    printf("========================================\n");
    printf("             Listado de usuarios\n");
    printf("========================================\n");

    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {
        printf("No hay usuarios cargados.\n");
        return;
    }

    while (fread(&usuario, sizeof(Usuario), 1, archivo) == 1)
    {
        if (usuario.activo)
        {
            mostrarUsuario(usuario);
            encontrados = 1;
        }
    }

    fclose(archivo);

    if (!encontrados)
    {
        printf("No hay usuarios activos.\n");
    }
}

void bajaUsuario(void)
{
    FILE *archivo;
    Usuario usuario;
    int id;
    long posicion;

    listarUsuarios();
    id = leerEntero("\nIngrese el ID del usuario a dar de baja: ");

    if (!buscarUsuarioPorId(id, &usuario, &posicion))
    {
        mostrarMensajeError("\nNo se encontro un usuario activo con ese ID.\n");
        pausar();
        return;
    }

    if (usuario.rol == ROL_ADMIN)
    {
        mostrarMensajeError("\nNo se puede dar de baja al administrador principal.\n");
        pausar();
        return;
    }

    if (!confirmar("Confirma la baja del usuario"))
    {
        mostrarMensajeError("\nOperacion cancelada.\n");
        pausar();
        return;
    }

    usuario.activo = 0;

    archivo = fopen(ARCHIVO_USUARIOS, "r+b");

    if (archivo == NULL)
    {
        mostrarMensajeError("\nNo se pudo abrir el archivo de usuarios.\n");
        pausar();
        return;
    }

    fseek(archivo, posicion, SEEK_SET);
    fwrite(&usuario, sizeof(Usuario), 1, archivo);
    fclose(archivo);

    mostrarMensajeExito("\nUsuario dado de baja correctamente.\n");
    pausar();
}

int obtenerSiguienteIdUsuario(void)
{
    FILE *archivo;
    Usuario usuario;
    int mayorId = 0;

    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {
        return 1;
    }

    while (fread(&usuario, sizeof(Usuario), 1, archivo) == 1)
    {
        if (usuario.id > mayorId)
        {
            mayorId = usuario.id;
        }
    }

    fclose(archivo);

    return mayorId + 1;
}

int existeUsuarioActivoConEmail(const char email[])
{
    FILE *archivo;
    Usuario usuario;

    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {
        return 0;
    }

    while (fread(&usuario, sizeof(Usuario), 1, archivo) == 1)
    {
        if (usuario.activo && strcmp(usuario.email, email) == 0)
        {
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

int buscarUsuarioPorLogin(const char email[], const char password[], Usuario *usuarioEncontrado)
{
    FILE *archivo;
    Usuario usuario;

    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {
        return 0;
    }

    while (fread(&usuario, sizeof(Usuario), 1, archivo) == 1)
    {
        if (usuario.activo && strcmp(usuario.email, email) == 0 && strcmp(usuario.password, password) == 0)
        {
            if (usuarioEncontrado != NULL)
            {
                *usuarioEncontrado = usuario;
            }

            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

int buscarUsuarioPorId(int id, Usuario *usuario, long *posicion)
{
    FILE *archivo;
    Usuario aux;
    long posActual;

    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if (archivo == NULL)
    {
        return 0;
    }

    while (fread(&aux, sizeof(Usuario), 1, archivo) == 1)
    {
        posActual = ftell(archivo) - sizeof(Usuario);

        if (aux.id == id && aux.activo)
        {
            if (usuario != NULL)
            {
                *usuario = aux;
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

void mostrarUsuario(Usuario usuario)
{
    printf("ID: %d | Nombre: %s | Email: %s | Rol: %s\n",
           usuario.id,
           usuario.nombre,
           usuario.email,
           usuario.rol == ROL_ADMIN ? "Administrador" : "Usuario");
}


int contarUsuarioActivos(void)
{

    FILE * archivo;
    Usuario usuario;
    int cantidad = 0;

    archivo = fopen(ARCHIVO_USUARIOS, "rb");

    if(archivo == NULL)

    {
        return 0;
    }

    while(fread(&usuario, sizeof(Usuario), 1, archivo))
    {
        if(usuario.activo)
        {
            cantidad++;
        }

    }

    fclose(archivo);

    return cantidad;
}
