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
        printf("\nNo se pudo crear el archivo de usuarios.\n");
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
    leerCadena(usuario.password, TAM_PASSWORD);

    if (strlen(usuario.nombre) == 0 || strlen(usuario.email) == 0 || strlen(usuario.password) == 0)
    {
        printf("\nTodos los campos son obligatorios.\n");
        pausar();
        return;
    }

    if (existeUsuarioActivoConEmail(usuario.email))
    {
        printf("\nYa existe un usuario activo con ese email.\n");
        pausar();
        return;
    }

    usuario.id = obtenerSiguienteIdUsuario();
    usuario.rol = ROL_USUARIO;
    usuario.activo = 1;

    archivo = fopen(ARCHIVO_USUARIOS, "ab");

    if (archivo == NULL)
    {
        printf("\nNo se pudo abrir el archivo de usuarios.\n");
        pausar();
        return;
    }

    fwrite(&usuario, sizeof(Usuario), 1, archivo);
    fclose(archivo);

    printf("\nUsuario registrado correctamente.\n");
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
    leerCadena(password, TAM_PASSWORD);

    if (buscarUsuarioPorLogin(email, password, usuarioLogueado))
    {
        printf("\nBienvenido/a, %s.\n", usuarioLogueado->nombre);
        pausar();
        return 1;
    }

    printf("\nEmail o password incorrectos.\n");
    pausar();
    return 0;
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
