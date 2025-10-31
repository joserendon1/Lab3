#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include "sistema.h"

bool guardarUsuarios();
bool cargarUsuarios();
bool buscarUsuario(const std::string& cedula, std::string& clave, double& saldo);
bool usuarioExiste(const std::string& cedula);
bool actualizarUsuario(const std::string& cedula, const std::string& clave, double saldo);
int contarUsuarios();

#endif
