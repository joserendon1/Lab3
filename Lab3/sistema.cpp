#include "sistema.h"
#include "usuarios.h"
#include "archivos.h"
#include "conversiones.h"
#include "metodo1.h"
#include "utilidades.h"
#include <iostream>
#include <sstream>
#include <fstream>

bool validarAdministrador() {
    try {
        std::string contrasenaCodificada = leerArchivo("sudo.txt");
        std::string contrasenaDecodificadaBinario = decodificarMetodo1(contrasenaCodificada, 8);
        std::string contrasenaDecodificada = binarioATexto(contrasenaDecodificadaBinario);

        std::string contrasenaIngresada;
        std::cout << "Ingrese la contrasena de administrador: ";
        std::getline(std::cin, contrasenaIngresada);

        return contrasenaDecodificada == contrasenaIngresada;
    } catch (const std::exception& e) {
        std::cout << "Error al validar administrador: " << e.what() << std::endl;
        return false;
    }
}

void menuAdministrador() {
    int opcion;
    do {
        std::cout << "\n---- MENU ADMINISTRADOR ----" << std::endl;
        std::cout << "1. Registrar usuario" << std::endl;
        std::cout << "2. Listar usuarios" << std::endl;
        std::cout << "3. Ver transacciones" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";

        if (!leerEntero(opcion)) continue;

        switch (opcion) {
        case 1:
            if (registrarUsuario()) {
                std::cout << "Usuario registrado exitosamente." << std::endl;
            } else {
                std::cout << "Error al registrar usuario." << std::endl;
            }
            break;
        case 2:
            std::cout << "\n---- USUARIOS REGISTRADOS ----" << std::endl;
            try {
                std::string usuariosCodificado = leerArchivo("usuarios.txt");
                if (usuariosCodificado.empty()) {
                    std::cout << "No hay usuarios registrados." << std::endl;
                } else {
                    std::string binarioDecodificado = decodificarMetodo1(usuariosCodificado, 8);
                    std::string usuariosDecodificado = binarioATexto(binarioDecodificado);
                    std::cout << "Usuarios:" << std::endl;
                    std::istringstream stream(usuariosDecodificado);
                    std::string linea;
                    int count = 0;
                    while (std::getline(stream, linea)) {
                        if (!linea.empty()) {
                            size_t pos1 = linea.find(',');
                            size_t pos2 = linea.find(',', pos1 + 1);
                            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                                std::string cedula = linea.substr(0, pos1);
                                std::string saldo = linea.substr(pos2 + 1);
                                std::cout << ++count << ". Cedula: " << cedula << ", Saldo: $" << saldo << std::endl;
                            }
                        }
                    }
                    if (count == 0) {
                        std::cout << "No hay usuarios registrados." << std::endl;
                    }
                }
            } catch (const std::exception& e) {
                std::cout << "No hay usuarios registrados." << std::endl;
            }
            break;
        case 3:
            mostrarTransacciones();
            break;
        case 4:
            std::cout << "Saliendo del menu administrador..." << std::endl;
            break;
        default:
            std::cout << "Opcion no valida." << std::endl;
        }
    } while (opcion != 4);
}

bool registrarUsuario() {
    std::string cedula, clave;
    double saldo;

    std::cout << "Ingrese cedula: ";
    std::getline(std::cin, cedula);

    // Validaciones robustas
    if (cedula.empty()) {
        std::cout << "La cedula no puede estar vacia." << std::endl;
        return false;
    }

    if (!validarCedula(cedula)) {
        std::cout << "Error: La cedula debe contener solo numeros y tener entre 6 y 12 digitos." << std::endl;
        return false;
    }

    if (usuarioExiste(cedula)) {
        std::cout << "Error: La cedula ya esta registrada." << std::endl;
        return false;
    }

    std::cout << "Ingrese clave: ";
    std::getline(std::cin, clave);

    if (clave.empty()) {
        std::cout << "La clave no puede estar vacia." << std::endl;
        return false;
    }

    // Validar que la clave no contenga comas (para evitar corrupción CSV)
    if (clave.find(',') != std::string::npos) {
        std::cout << "Error: La clave no puede contener comas." << std::endl;
        return false;
    }

    std::cout << "Ingrese saldo inicial: ";
    std::cin >> saldo;
    limpiarBuffer();

    if (saldo < 0) {
        std::cout << "El saldo no puede ser negativo." << std::endl;
        return false;
    }

    return actualizarUsuario(cedula, clave, saldo);
}

bool iniciarSesionCliente(std::string& cedula, std::string& clave, double& saldo) {
    std::string cedulaIngresada, claveIngresada;

    std::cout << "Ingrese su cedula: ";
    std::getline(std::cin, cedulaIngresada);

    std::cout << "Ingrese su clave: ";
    std::getline(std::cin, claveIngresada);

    std::string claveAlmacenada;
    double saldoAlmacenado;

    if (buscarUsuario(cedulaIngresada, claveAlmacenada, saldoAlmacenado) &&
        claveAlmacenada == claveIngresada) {

        cedula = cedulaIngresada;
        clave = claveIngresada;
        saldo = saldoAlmacenado;

        if (saldo >= 1000) {
            saldo -= 1000;
            actualizarUsuario(cedula, clave, saldo);
            registrarTransaccion(cedula, "COSTO_INGRESO", 1000);
            std::cout << "Se ha cobrado $1000 por ingreso al sistema." << std::endl;
            return true;
        } else {
            std::cout << "Saldo insuficiente para cubrir el costo de ingreso." << std::endl;
            return false;
        }
    }

    std::cout << "Cedula o clave incorrectas." << std::endl;
    return false;
}

void consultarSaldo(const std::string& cedula, double saldo) {
    std::cout << "Su saldo actual es: $" << saldo << std::endl;
    registrarTransaccion(cedula, "CONSULTA_SALDO", 0);
}

void retirarDinero(std::string& cedula, double& saldo) {
    double monto;
    std::cout << "Ingrese el monto a retirar: ";
    std::cin >> monto;
    limpiarBuffer();

    if (monto <= 0) {
        std::cout << "El monto debe ser positivo." << std::endl;
        return;
    }

    if (saldo >= monto) {
        saldo -= monto;

        std::string clave;
        double saldoDummy;
        if (buscarUsuario(cedula, clave, saldoDummy)) {
            actualizarUsuario(cedula, clave, saldo);
        }

        registrarTransaccion(cedula, "RETIRO", monto);
        std::cout << "Retiro exitoso. Nuevo saldo: $" << saldo << std::endl;
    } else {
        std::cout << "Saldo insuficiente." << std::endl;
    }
}

void registrarTransaccion(const std::string& cedula, const std::string& tipo, double monto) {
    try {
        std::string transaccion = "Cedula: " + cedula +
                                  ", Tipo: " + tipo +
                                  ", Monto: $" + std::to_string((int)monto);

        std::string binario = textoABinario(transaccion);
        std::string transaccionCodificada = codificarMetodo1(binario, 8);
        std::ofstream archivo("transacciones.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << transaccionCodificada << "###\n";
            archivo.close();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error al registrar transaccion: " << e.what() << std::endl;
    }
}

void menuCliente() {
    std::string cedula, clave;
    double saldo;

    if (!iniciarSesionCliente(cedula, clave, saldo)) {
        return;
    }

    int opcion;
    do {
        std::cout << "\n---- MENU CLIENTE ----" << std::endl;
        std::cout << "1. Consultar saldo" << std::endl;
        std::cout << "2. Retirar dinero" << std::endl;
        std::cout << "3. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";

        if (!leerEntero(opcion)) continue;

        switch (opcion) {
        case 1:
            consultarSaldo(cedula, saldo);
            break;
        case 2:
            retirarDinero(cedula, saldo);
            break;
        case 3:
            std::cout << "Saliendo del sistema..." << std::endl;
            break;
        default:
            std::cout << "Opcion no valida." << std::endl;
        }
    } while (opcion != 3);
}

void ejecutarSistemaBancario() {
    if (!cargarUsuarios()) {
        std::cout << "No se pudieron cargar los usuarios." << std::endl;
    }

    int opcion;
    do {
        std::cout << "\n---- SISTEMA BANCARIO ----" << std::endl;
        std::cout << "1. Ingresar como administrador" << std::endl;
        std::cout << "2. Ingresar como cliente" << std::endl;
        std::cout << "3. Volver al menu principal" << std::endl;
        std::cout << "Seleccione una opcion: ";

        if (!leerEntero(opcion)) continue;

        switch (opcion) {
        case 1:
            if (validarAdministrador()) {
                std::cout << "Acceso concedido." << std::endl;
                menuAdministrador();
            } else {
                std::cout << "Acceso denegado." << std::endl;
            }
            break;
        case 2:
            menuCliente();
            break;
        case 3:
            std::cout << "Volviendo al menu principal..." << std::endl;
            break;
        default:
            std::cout << "Opcion no valida." << std::endl;
        }
    } while (opcion != 3);
}

void mostrarTransacciones() {
    try {
        std::cout << "\n---- HISTORIAL DE TRANSACCIONES ----" << std::endl;

        std::ifstream test("transacciones.txt");
        if (!test.is_open()) {
            std::cout << "No hay transacciones registradas." << std::endl;
            return;
        }
        test.close();

        std::string contenidoCompleto = leerArchivo("transacciones.txt");
        if (contenidoCompleto.empty()) {
            std::cout << "No hay transacciones registradas." << std::endl;
            return;
        }

        int count = 0;
        size_t inicio = 0;
        size_t fin = contenidoCompleto.find("###");

        while (fin != std::string::npos) {
            std::string transaccionCodificada = contenidoCompleto.substr(inicio, fin - inicio);
            std::string transaccionLimpia;
            for (size_t i = 0; i < transaccionCodificada.length(); i++) {
                char c = transaccionCodificada[i];
                if (c == '0' || c == '1') {
                    transaccionLimpia += c;
                }
            }
            if (!transaccionLimpia.empty() && transaccionLimpia.length() % 8 == 0) {
                try {
                    std::string binarioDecodificado = decodificarMetodo1(transaccionLimpia, 8);
                    std::string transaccionTexto = binarioATexto(binarioDecodificado);
                    std::string textoLimpio;
                    for (size_t i = 0; i < transaccionTexto.length(); i++) {
                        char c = transaccionTexto[i];
                        if (c >= 32 && c <= 126) {
                            textoLimpio += c;
                        }
                    }

                    if (!textoLimpio.empty()) {
                        std::cout << ++count << ". " << textoLimpio << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cout << "Error en transacción " << (count + 1) << ": " << e.what() << std::endl;
                }
            }
            inicio = fin + 3;
            fin = contenidoCompleto.find("###", inicio);
        }

        if (count == 0) {
            std::cout << "No hay transacciones válidas para mostrar." << std::endl;
        } else {
            std::cout << "Total de transacciones: " << count << std::endl;
        }

    } catch (const std::exception& e) {
        std::cout << "Error al leer transacciones: " << e.what() << std::endl;
    }
}

bool validarCedula(const std::string& cedula) {
    if (cedula.empty()) {
        return false;
    }

    for (char c : cedula) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    if (cedula.length() < 6 || cedula.length() > 12) {
        return false;
    }

    return true;
}
