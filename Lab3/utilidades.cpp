#include "utilidades.h"
#include "archivos.h"
#include "conversiones.h"
#include "metodo1.h"
#include "metodo2.h"
#include <iostream>

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

        std::cout << "Nombre del archivo de salida: ";
        std::getline(std::cin, archivoSalida);

        std::cout << "Metodo (1 o 2): ";
        std::cin >> metodo;

        std::cout << "Semilla (entero positivo): ";
        std::cin >> semilla;
        std::cin.ignore();

        if (metodo != 1 && metodo != 2) {
            throw std::invalid_argument("Metodo debe ser 1 o 2");
        }
        if (semilla <= 0) {
            throw std::invalid_argument("Semilla debe ser mayor a 0");
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
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void decodificarArchivo() {
    try {
        std::string archivoEntrada, archivoSalida;
        int metodo, semilla;

        std::cout << "----DECODIFICAR ARCHIVO----" << std::endl;
        std::cout << "Nombre del archivo codificado: ";
        std::getline(std::cin, archivoEntrada);

        std::cout << "Nombre del archivo de salida: ";
        std::getline(std::cin, archivoSalida);

        std::cout << "Metodo (1 o 2): ";
        std::cin >> metodo;

        std::cout << "Semilla (entero positivo): ";
        std::cin >> semilla;
        std::cin.ignore();

        if (metodo != 1 && metodo != 2) {
            throw std::invalid_argument("Metodo debe ser 1 o 2");
        }
        if (semilla <= 0) {
            throw std::invalid_argument("Semilla debe ser mayor a 0");
        }

        std::string binarioCodificado = leerArchivo(archivoEntrada);
        std::cout << "Binario codificado leido: " << binarioCodificado.length() << " bits" << std::endl;

        std::string binarioDecodificado;
        if (metodo == 1) {
            binarioDecodificado = decodificarMetodo1(binarioCodificado, semilla);
        } else {
            binarioDecodificado = decodificarMetodo2(binarioCodificado, semilla);
        }

        std::string textoDecodificado = binarioATexto(binarioDecodificado);
        escribirArchivo(archivoSalida, textoDecodificado);

        std::cout << "----DECODIFICACION EXITOSA----" << std::endl;
        std::cout << "Texto decodificado: " << textoDecodificado.length() << " caracteres" << std::endl;
        std::cout << "Archivo guardado en: " << archivoSalida << std::endl;
        std::cout << "Primeros 50 caracteres: " << textoDecodificado.substr(0, 50) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void mostrarUso() {
    std::cout << "Uso del programa:" << std::endl;
    std::cout << "1. Seleccione 'Codificar archivo' para codificar un archivo de texto" << std::endl;
    std::cout << "2. Seleccione 'Decodificar archivo' para decodificar un archivo binario" << std::endl;
    std::cout << std::endl;
}
