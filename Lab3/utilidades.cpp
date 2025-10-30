#include "utilidades.h"
#include "archivos.h"
#include "conversiones.h"
#include "metodo1.h"
#include "metodo2.h"
#include <iostream>
#include <stdexcept>

void limpiarBuffer() {
    std::cin.clear();
    while (std::cin.get() != '\n') {
        if (std::cin.eof()) break;
    }
}

bool leerEntero(int& valor) {
    if (std::cin >> valor) {
        limpiarBuffer();
        return true;
    } else {
        std::cout << "Error: Por favor ingrese un numero entero valido." << std::endl;
        limpiarBuffer();
        return false;
    }
}

void mostrarMenu() {
    std::cout << "----PROGRAMA DE CODIFICACION/DECODIFICACION----" << std::endl;
    std::cout << "1. Codificar archivo" << std::endl;
    std::cout << "2. Decodificar archivo" << std::endl;
    std::cout << "3. Salir" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
}

void codificarArchivo() {
    try {
        std::string archivoEntrada, archivoSalida;
        int metodo, semilla;

        std::cout << "----CODIFICAR ARCHIVO----" << std::endl;
        std::cout << "Nombre del archivo de entrada: ";
        std::getline(std::cin, archivoEntrada);

        if (archivoEntrada.empty()) {
            throw std::invalid_argument("Error: El nombre del archivo no puede estar vacio");
        }

        std::cout << "Nombre del archivo de salida: ";
        std::getline(std::cin, archivoSalida);

        if (archivoSalida.empty()) {
            throw std::invalid_argument("Error: El nombre del archivo de salida no puede estar vacio");
        }

        std::cout << "Metodo (1 o 2): ";
        if (!leerEntero(metodo)) {
            return;
        }

        std::cout << "Semilla (entero positivo): ";
        if (!leerEntero(semilla)) {
            return;
        }

        if (metodo != 1 && metodo != 2) {
            throw std::invalid_argument("Error: Metodo debe ser 1 o 2");
        }
        if (semilla <= 0) {
            throw std::invalid_argument("Error: Semilla debe ser mayor a 0");
        }

        std::string texto = leerArchivo(archivoEntrada);
        std::string binario = textoABinario(texto);

        std::cout << "Texto leido: " << texto.length() << " caracteres" << std::endl;
        std::cout << "Binario generado: " << binario.length() << " bits" << std::endl;

        std::string binarioCodificado;
        if (metodo == 1) {
            binarioCodificado = codificarMetodo1(binario, semilla);
            std::cout << "Usando Metodo 1 de codificacion" << std::endl;
        } else {
            binarioCodificado = codificarMetodo2(binario, semilla);
            std::cout << "Usando Metodo 2 de codificacion" << std::endl;
        }

        escribirArchivo(archivoSalida, binarioCodificado);

        std::cout << "----CODIFICACION EXITOSA----" << std::endl;
        std::cout << "Binario codificado: " << binarioCodificado.length() << " bits" << std::endl;
        std::cout << "Archivo guardado en: " << archivoSalida << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido durante la codificacion" << std::endl;
    }
}

void decodificarArchivo() {
    try {
        std::string archivoEntrada, archivoSalida;
        int metodo, semilla;

        std::cout << "----DECODIFICAR ARCHIVO----" << std::endl;
        std::cout << "Nombre del archivo codificado: ";
        std::getline(std::cin, archivoEntrada);

        if (archivoEntrada.empty()) {
            throw std::invalid_argument("Error: El nombre del archivo no puede estar vacio");
        }

        std::cout << "Nombre del archivo de salida: ";
        std::getline(std::cin, archivoSalida);

        if (archivoSalida.empty()) {
            throw std::invalid_argument("Error: El nombre del archivo de salida no puede estar vacio");
        }

        std::cout << "Metodo (1 o 2): ";
        if (!leerEntero(metodo)) {
            return;
        }

        std::cout << "Semilla (entero positivo): ";
        if (!leerEntero(semilla)) {
            return;
        }

        if (metodo != 1 && metodo != 2) {
            throw std::invalid_argument("Error: Metodo debe ser 1 o 2");
        }
        if (semilla <= 0) {
            throw std::invalid_argument("Error: Semilla debe ser mayor a 0");
        }

        std::string binarioCodificado = leerArchivo(archivoEntrada);
        std::cout << "Binario codificado leido: " << binarioCodificado.length() << " bits" << std::endl;

        std::string binarioDecodificado;
        if (metodo == 1) {
            binarioDecodificado = decodificarMetodo1(binarioCodificado, semilla);
        } else {
            binarioDecodificado = decodificarMetodo2(binarioCodificado, semilla);
        }

        std::cout << "Binario decodificado: " << binarioDecodificado.length() << " bits" << std::endl;

        size_t longitudOriginal = binarioDecodificado.length();
        size_t bitsNecesarios = (longitudOriginal + 7) / 8 * 8;

        if (longitudOriginal < bitsNecesarios) {
            std::cout << "Ajustando longitud: agregando " << (bitsNecesarios - longitudOriginal)
            << " bits de relleno" << std::endl;
            binarioDecodificado.append(bitsNecesarios - longitudOriginal, '0');
        } else if (longitudOriginal > bitsNecesarios) {
            std::cout << "Ajustando longitud: removiendo " << (longitudOriginal - bitsNecesarios)
            << " bits sobrantes" << std::endl;
            binarioDecodificado = binarioDecodificado.substr(0, bitsNecesarios);
        }

        std::string textoDecodificado = binarioATexto(binarioDecodificado);
        escribirArchivo(archivoSalida, textoDecodificado);

        std::cout << "----DECODIFICACION EXITOSA----" << std::endl;
        std::cout << "Texto decodificado: " << textoDecodificado.length() << " caracteres" << std::endl;
        std::cout << "Archivo guardado en: " << archivoSalida << std::endl;

        if (!textoDecodificado.empty()) {
            size_t previewLength = (textoDecodificado.length() < 50) ? textoDecodificado.length() : 50;
            std::cout << "Primeros " << previewLength << " caracteres: "
                      << textoDecodificado.substr(0, previewLength) << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error desconocido durante la decodificacion" << std::endl;
    }
}

void mostrarUso() {
    std::cout << "Uso del programa:" << std::endl;
    std::cout << "1. Seleccione 'Codificar archivo' para codificar un archivo de texto" << std::endl;
    std::cout << "2. Seleccione 'Decodificar archivo' para decodificar un archivo binario" << std::endl;
    std::cout << std::endl;
}
