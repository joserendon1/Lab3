#include <iostream>
#include "utilidades.h"

int main() {

    int opcion;

    std::cout << "----PROGRAMA DE CODIFICACION/DECODIFICACION----" << std::endl;
    std::cout << "Bienvenido. Asegurese de tener los archivos necesarios en el directorio." << std::endl;
    std::cout << std::endl;

    do {
        mostrarMenu();
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            codificarArchivo();
            break;
        case 2:
            decodificarArchivo();
            break;
        case 3:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
        }
        std::cout << std::endl;

    } while (opcion != 3);

    return 0;
}
