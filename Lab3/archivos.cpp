#include "archivos.h"
#include <stdexcept>

std::string leerArchivo(const std::string& nombreArchivo) {
    if (nombreArchivo.empty()) {
        throw std::invalid_argument("Error: Nombre de archivo vacio");
    }

    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error: No se pudo abrir el archivo " + nombreArchivo);
    }

    archivo.seekg(0, std::ios::end);
    if (archivo.tellg() == 0) {
        archivo.close();
        throw std::runtime_error("Error: El archivo " + nombreArchivo + " esta vacio");
    }
    archivo.seekg(0, std::ios::beg);

    std::string contenido;
    char caracter;
    while (archivo.get(caracter)) {
        contenido += caracter;
    }

    if (!archivo.eof() && archivo.fail()) {
        archivo.close();
        throw std::runtime_error("Error: Fallo la lectura del archivo " + nombreArchivo);
    }

    archivo.close();
    return contenido;
}

void escribirArchivo(const std::string& nombreArchivo, const std::string& contenido) {
    if (nombreArchivo.empty()) {
        throw std::invalid_argument("Error: Nombre de archivo vacio");
    }

    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error: No se pudo crear el archivo " + nombreArchivo);
    }

    archivo << contenido;

    if (archivo.fail()) {
        archivo.close();
        throw std::runtime_error("Error: Fallo la escritura en el archivo " + nombreArchivo);
    }

    archivo.close();
}
