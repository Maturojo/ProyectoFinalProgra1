#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

#include "estructuras.h"

#define ARCHIVO_USUARIOS "usuarios.dat"
#define ROL_ADMIN 1
#define ROL_USUARIO 2

void inicializarUsuarios();
void menuUsuarios();
void registrarUsuario();
int loginUsuario(Usuario *usuarioLogueado);
void listarUsuarios();
void bajaUsuario();

int obtenerSiguienteIdUsuario();
int existeUsuarioActivoConEmail(const char email[]);
int buscarUsuarioPorLogin(const char email[], const char password[], Usuario *usuarioEncontrado);
int buscarUsuarioPorId(int id, Usuario *usuario, long *posicion);
void mostrarUsuario(Usuario usuario);

int contarUsuarioActivos();
#endif
