#include "metodo1.h"
#include "bloques.h"
#include <stdexcept>

std::string invertirBits(const std::string& bloque) {
    if (bloque.empty()) {
        throw std::invalid_argument("Error: Bloque vacio para invertir bits");
    }

    std::string resultado;
    for (size_t i = 0; i < bloque.length(); i++) {
        if (bloque[i] != '0' && bloque[i] != '1') {
            throw std::invalid_argument("Error: Bloque contiene caracteres no binarios");
        }
        resultado += (bloque[i] == '0') ? '1' : '0';
    }
    return resultado;
}

std::string invertirCadaDosBits(const std::string& bloque) {
    if (bloque.empty()) {
        throw std::invalid_argument("Error: Bloque vacio para inversion cada 2 bits");
    }

    if (bloque.length() < 2) {
        throw std::invalid_argument("Error: Bloque muy pequeño para inversion cada 2 bits");
    }

    std::string resultado = bloque;
    for (size_t pos = 1; pos < resultado.length(); pos += 2) {
        resultado[pos] = (resultado[pos] == '0') ? '1' : '0';
    }
    return resultado;
}

std::string invertirCadaTresBits(const std::string& bloque) {
    if (bloque.empty()) {
        throw std::invalid_argument("Error: Bloque vacio para inversion cada 3 bits");
    }

    if (bloque.length() < 3) {
        throw std::invalid_argument("Error: Bloque muy pequeño para inversion cada 3 bits");
    }

    std::string resultado = bloque;
    for (size_t i = 2; i < resultado.length(); i += 3) {
        resultado[i] = (resultado[i] == '0') ? '1' : '0';
    }
    return resultado;
}

std::string codificarMetodo1(const std::string& binario, int n) {
    if (binario.empty()) {
        throw std::invalid_argument("Error: Binario vacio para codificar");
    }

    if (n <= 0) {
        throw std::invalid_argument("Error: Semilla debe ser mayor a 0");
    }

    int numBloques;
    std::string* bloques = dividirEnBloques(binario, n, numBloques);
    std::string* bloquesOriginales = new std::string[numBloques];

    for (int i = 0; i < numBloques; i++) {
        bloquesOriginales[i] = bloques[i];
    }

    for (int i = 0; i < numBloques; i++) {
        if (i == 0) {
            bloques[i] = invertirBits(bloques[i]);
        } else {
            int unos = contarUnos(bloquesOriginales[i - 1]);
            int ceros = n - unos;

            if (unos == ceros) {
                bloques[i] = invertirBits(bloques[i]);
            } else if (ceros > unos) {
                bloques[i] = invertirCadaDosBits(bloques[i]);
            } else {
                bloques[i] = invertirCadaTresBits(bloques[i]);
            }
        }
    }

    std::string resultado = unirBloques(bloques, numBloques);
    delete[] bloques;
    delete[] bloquesOriginales;
    return resultado;
}

std::string decodificarMetodo1(const std::string& binario, int n) {
    if (binario.empty()) {
        throw std::invalid_argument("Error: Binario vacio para decodificar");
    }

    if (n <= 0) {
        throw std::invalid_argument("Error: Semilla debe ser mayor a 0");
    }

    int numBloques;
    std::string* bloques = dividirEnBloques(binario, n, numBloques);

    for (int i = 0; i < numBloques; i++) {
        if (i == 0) {
            bloques[i] = invertirBits(bloques[i]);
        } else {
            int unos = contarUnos(bloques[i - 1]);
            int ceros = n - unos;

            if (unos == ceros) {
                bloques[i] = invertirBits(bloques[i]);
            } else if (ceros > unos) {
                bloques[i] = invertirCadaDosBits(bloques[i]);
            } else {
                bloques[i] = invertirCadaTresBits(bloques[i]);
            }
        }
    }

    std::string resultado = unirBloques(bloques, numBloques);
    delete[] bloques;
    return resultado;
}
