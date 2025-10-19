#include <iostream>
#include <fstream>
#include <string>

std::string leerArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error: No se pudo abrir el archivo " + nombreArchivo);
    }

    std::string contenido;
    char caracter;
    while (archivo.get(caracter)) {
        contenido += caracter;
    }

    archivo.close();
    return contenido;
}

void escribirArchivo(const std::string& nombreArchivo, const std::string& contenido) {
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error: No se pudo crear el archivo " + nombreArchivo);
    }

    archivo << contenido;
    archivo.close();
}

int main() {
    std::cout << "Pruebas de Archivos" << std::endl;

    try {

        std::cout << "1. Probando escritura y lectura..." << std::endl;
        escribirArchivo("prueba1.txt", "Hola Buenas Tardes");
        std::string contenido = leerArchivo("prueba1.txt");
        std::cout << "Contenido leido: '" << contenido << "'" << std::endl;
        std::cout << "\n2. Probando archivo multilinea..." << std::endl;
        escribirArchivo("prueba2.txt", "Linea 1\nLinea 2\nLinea 3");
        contenido = leerArchivo("prueba2.txt");
        std::cout << "Contenido multilinea leido correctamente" << std::endl;
        std::cout << "\n3. Probando manejo de errores..." << std::endl;

        try {
            contenido = leerArchivo("archivo_inexistente.txt");
        } catch (const std::exception& e) {
            std::cout << "Error manejado correctamente: " << e.what() << std::endl;
        }


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
