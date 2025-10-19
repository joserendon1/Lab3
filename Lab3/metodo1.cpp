#include "metodo1.h"
#include "bloques.h"

std::string invertirBits(const std::string& bloque) {
    std::string resultado;
    for (char bit : bloque) {
        resultado += (bit == '0') ? '1' : '0';
    }
    return resultado;
}

std::string invertirCadaDosBits(const std::string& bloque) {
    std::string resultado = bloque;
    if (resultado.length() > 1) {
        resultado[1] = (resultado[1] == '0') ? '1' : '0';
    }
    if (resultado.length() > 3) {
        resultado[3] = (resultado[3] == '0') ? '1' : '0';
    }
    return resultado;
}

std::string invertirCadaTresBits(const std::string& bloque) {
    std::string resultado = bloque;
    if (resultado.length() > 0) {
        resultado[0] = (resultado[0] == '0') ? '1' : '0';
    }
    if (resultado.length() > 2) {
        resultado[2] = (resultado[2] == '0') ? '1' : '0';
    }
    return resultado;
}

std::string codificarMetodo1(const std::string& binario, int n) {
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
