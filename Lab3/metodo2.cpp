#include "metodo2.h"
#include "bloques.h"

std::string desplazarBits(const std::string& bloque) {
    if (bloque.empty()) return bloque;

    std::string resultado = bloque;
    char ultimoBit = resultado[resultado.length() - 1];
    for (size_t i = resultado.length() - 1; i > 0; i--) {
        resultado[i] = resultado[i - 1];
    }
    resultado[0] = ultimoBit;

    return resultado;
}

std::string codificarMetodo2(const std::string& binario, int n) {
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
    int numBloques;
    std::string* bloques = dividirEnBloques(binario, n, numBloques);

    for (int i = 0; i < numBloques; i++) {
        std::string bloque = bloques[i];
        if (bloque.empty()) continue;

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
