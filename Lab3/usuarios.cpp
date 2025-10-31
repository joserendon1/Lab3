#include "usuarios.h"
#include "archivos.h"
#include "conversiones.h"
#include "metodo1.h"
#include <sstream>
#include <fstream>
#include <iostream>

bool guardarUsuarios() {
    return true;
}

bool cargarUsuarios() {
    return true;
}

bool buscarUsuario(const std::string& cedula, std::string& clave, double& saldo) {
    try {
        // Validar cédula de búsqueda
        if (!validarCedula(cedula)) {
            return false;
        }

        std::ifstream test("usuarios.txt");
        if (!test.is_open()) {
            return false;
        }
        test.close();

        std::string codificado = leerArchivo("usuarios.txt");
        if (codificado.empty()) {
            return false;
        }

        std::string binarioDecodificado = decodificarMetodo1(codificado, 8);
        std::string contenido = binarioATexto(binarioDecodificado);
        std::istringstream stream(contenido);
        std::string linea;

        while (std::getline(stream, linea)) {
            if (linea.empty()) continue;

            size_t pos1 = linea.find(',');
            size_t pos2 = linea.find(',', pos1 + 1);

            // Validar formato antes de procesar
            if (pos1 == std::string::npos || pos2 == std::string::npos) {
                continue; // Omitir línea corrupta
            }

            std::string cedulaArchivo = linea.substr(0, pos1);

            // Validar cédula del archivo
            if (!validarCedula(cedulaArchivo)) {
                continue; // Omitir cédula inválida
            }

            if (cedulaArchivo == cedula) {
                clave = linea.substr(pos1 + 1, pos2 - pos1 - 1);

                try {
                    saldo = std::stod(linea.substr(pos2 + 1));
                } catch (const std::invalid_argument& e) {
                    throw std::runtime_error("Error: Formato de saldo invalido para usuario " + cedula);
                } catch (const std::out_of_range& e) {
                    throw std::runtime_error("Error: Saldo fuera de rango para usuario " + cedula);
                }

                return true;
            }
        }
        return false;
    } catch (...) {
        return false;
    }
}

bool usuarioExiste(const std::string& cedula) {
    std::string clave;
    double saldo;
    return buscarUsuario(cedula, clave, saldo);
}

bool actualizarUsuario(const std::string& cedula, const std::string& clave, double saldo) {
    try {
        // Validar parámetros de entrada
        if (cedula.find(',') != std::string::npos || clave.find(',') != std::string::npos) {
            throw std::invalid_argument("Error: Cedula o clave contienen caracteres invalidos (comas)");
        }

        std::string nuevoContenido = "";
        bool usuarioEncontrado = false;

        std::ifstream test("usuarios.txt");
        if (test.is_open()) {
            test.close();

            std::string codificado = leerArchivo("usuarios.txt");
            if (!codificado.empty()) {
                std::string binarioDecodificado = decodificarMetodo1(codificado, 8);
                std::string contenido = binarioATexto(binarioDecodificado);
                std::istringstream stream(contenido);
                std::string linea;

                while (std::getline(stream, linea)) {
                    if (linea.empty()) continue;

                    // Validar formato de línea más estricto
                    size_t pos1 = linea.find(',');
                    size_t pos2 = linea.find(',', pos1 + 1);

                    if (pos1 == std::string::npos || pos2 == std::string::npos) {
                        // Línea corrupta - omitir o loggear
                        std::cerr << "Advertencia: Linea con formato invalido omitida: " << linea << std::endl;
                        continue;
                    }

                    std::string cedulaArchivo = linea.substr(0, pos1);

                    // Validar cédula en archivo
                    if (!validarCedula(cedulaArchivo)) {
                        std::cerr << "Advertencia: Cedula invalida en archivo: " << cedulaArchivo << std::endl;
                        continue;
                    }

                    if (cedulaArchivo == cedula) {
                        nuevoContenido += cedula + "," + clave + "," + std::to_string((int)saldo) + "\n";
                        usuarioEncontrado = true;
                    } else {
                        nuevoContenido += linea + "\n";
                    }
                }
            }
        }

        if (!usuarioEncontrado) {
            nuevoContenido += cedula + "," + clave + "," + std::to_string((int)saldo) + "\n";
        }

        std::string binario = textoABinario(nuevoContenido);
        std::string codificado = codificarMetodo1(binario, 8);
        escribirArchivo("usuarios.txt", codificado);
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error en actualizarUsuario: " << e.what() << std::endl;
        return false;
    }
}

int contarUsuarios() {
    try {
        std::ifstream test("usuarios.txt");
        if (!test.is_open()) return 0;
        test.close();

        std::string codificado = leerArchivo("usuarios.txt");
        if (codificado.empty()) return 0;

        std::string contenido = decodificarMetodo1(codificado, 8);

        int count = 0;
        std::istringstream stream(contenido);
        std::string linea;
        while (std::getline(stream, linea)) {
            if (!linea.empty()) count++;
        }
        return count;
    } catch (...) {
        return 0;
    }
}
