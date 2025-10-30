#include <iostream>
#include "utilidades.h"

int main() {
    std::cout << "----PROGRAMA DE CODIFICACION/DECODIFICACION----" << std::endl;
    std::cout << "Bienvenido. Asegurese de tener los archivos necesarios en el directorio." << std::endl;

    int opcion;

    do {
        try {
            mostrarMenu();
            std::cout << "Seleccione una opcion: ";

            if (!leerEntero(opcion)) {
                continue;
            }

            switch (opcion) {
            case 1:
                std::cout << "\n[Seleccionado: Codificar archivo]" << std::endl;
                codificarArchivo();
                break;
            case 2:
                std::cout << "\n[Seleccionado: Decodificar archivo]" << std::endl;
                decodificarArchivo();
                break;
            case 3:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Error: Opcion no valida. Por favor seleccione 1, 2 o 3." << std::endl;
            }

        } catch (const std::exception& e) {
            std::cerr << "Error inesperado en el menu: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Error desconocido en el menu." << std::endl;
        }

        std::cout << std::endl;

    } while (opcion != 3);

    std::cout << "Programa terminado. ¡Hasta luego!" << std::endl;
    return 0;
}
