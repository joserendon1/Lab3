#include "bloques.h"

std::string* dividirEnBloques(const std::string& binario, int n, int& numBloques) {
    size_t longitud = binario.length();
    numBloques = (longitud + n - 1) / n;
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
    std::string resultado;
    for (int i = 0; i < numBloques; i++) {
        resultado += bloques[i];
    }
    return resultado;
}

int contarUnos(const std::string& bloque) {
    int count = 0;
    for (char bit : bloque) {
        if (bit == '1') count++;
    }
    return count;
}
