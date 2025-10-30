#include "metodo2.h"
#include "bloques.h"
#include <stdexcept>

std::string desplazarBits(const std::string& bloque) {
    if (bloque.empty()) {
        throw std::invalid_argument("Error: Bloque vacio para desplazar");
    }

    for (size_t i = 0; i < bloque.length(); i++) {
        if (bloque[i] != '0' && bloque[i] != '1') {
            throw std::invalid_argument("Error: Bloque contiene caracteres no binarios");
        }
    }

    std::string resultado = bloque;
    char ultimoBit = resultado[resultado.length() - 1];
    for (size_t i = resultado.length() - 1; i > 0; i--) {
        resultado[i] = resultado[i - 1];
    }
    resultado[0] = ultimoBit;

    return resultado;
}

std::string codificarMetodo2(const std::string& binario, int n) {
    if (binario.empty()) {
        throw std::invalid_argument("Error: Binario vacio para codificar");
    }

    if (n <= 0) {
        throw std::invalid_argument("Error: Semilla debe ser mayor a 0");
    }

    int numBloques;
    std::string* bloques = dividirEnBloques(binario, n, numBloques);

    for (int i = 0; i < numBloques; i++) {
        bloques[i] = desplazarBits(bloques[i]);
    }

    std::string resultado = unirBloques(bloques, numBloques);
    delete[] bloques;
    return resultado;
}

std::string decodificarMetodo2(const std::string& binario, int n) {
    if (binario.empty()) {
        throw std::invalid_argument("Error: Binario vacio para decodificar");
    }

    if (n <= 0) {
        throw std::invalid_argument("Error: Semilla debe ser mayor a 0");
    }

    int numBloques;
    std::string* bloques = dividirEnBloques(binario, n, numBloques);

    for (int i = 0; i < numBloques; i++) {
        std::string bloque = bloques[i];
        if (bloque.empty()) continue;

        for (size_t j = 0; j < bloque.length(); j++) {
            if (bloque[j] != '0' && bloque[j] != '1') {
                delete[] bloques;
                throw std::invalid_argument("Error: Bloque contiene caracteres no binarios");
            }
        }

        char primerBit = bloque[0];
        for (size_t j = 0; j < bloque.length() - 1; j++) {
            bloque[j] = bloque[j + 1];
        }
        bloque[bloque.length() - 1] = primerBit;
        bloques[i] = bloque;
    }

    std::string resultado = unirBloques(bloques, numBloques);
    delete[] bloques;
    return resultado;
}
