#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>

void ejecutarSistemaBancario();
bool validarAdministrador();
void menuAdministrador();
void menuCliente();
bool registrarUsuario();
bool iniciarSesionCliente(std::string& cedula, std::string& clave, double& saldo);
void consultarSaldo(const std::string& cedula, double saldo);
void retirarDinero(std::string& cedula, double& saldo);
void registrarTransaccion(const std::string& cedula, const std::string& tipo, double monto);
void mostrarTransacciones();
bool validarCedula(const std::string& cedula);

#endif
