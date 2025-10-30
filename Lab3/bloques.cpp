#include "bloques.h"
#include <stdexcept>

std::string* dividirEnBloques(const std::string& binario, int n, int& numBloques) {
    if (n <= 0) {
        throw std::invalid_argument("Error: El tamaño del bloque debe ser mayor a 0");
    }

    if (binario.empty()) {
        throw std::invalid_argument("Error: La cadena binaria esta vacia");
    }

    for (size_t i = 0; i < binario.length(); i++) {
        if (binario[i] != '0' && binario[i] != '1') {
            throw std::invalid_argument("Error: La cadena contiene caracteres no binarios");
        }
    }

    size_t longitud = binario.length();
    numBloques = (longitud + n - 1) / n;

    if (numBloques <= 0) {
        throw std::runtime_error("Error: No se pueden crear bloques con los parametros dados");
    }

    std::string* bloques = new std::string[numBloques];

    for (int i = 0; i < numBloques; i++) {
        size_t inicio = i * n;
        size_t longitudBloque = n;
        if (inicio + longitudBloque > longitud) {
            longitudBloque = longitud - inicio;
        }
        bloques[i] = binario.substr(inicio, longitudBloque);

        while (bloques[i].length() < static_cast<size_t>(n)) {
            bloques[i] += '0';
        }
    }
    return bloques;
}

std::string unirBloques(std::string* bloques, int numBloques) {
    if (bloques == nullptr) {
        throw std::invalid_argument("Error: Arreglo de bloques es nulo");
    }

    if (numBloques <= 0) {
        throw std::invalid_argument("Error: Numero de bloques invalido");
    }

    std::string resultado;
    for (int i = 0; i < numBloques; i++) {
        resultado += bloques[i];
    }
    return resultado;
}

int contarUnos(const std::string& bloque) {
    if (bloque.empty()) {
        return 0;
    }

    int count = 0;
    for (size_t i = 0; i < bloque.length(); i++) {
        if (bloque[i] == '1') count++;
    }
    return count;
}
