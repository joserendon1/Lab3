#include "conversiones.h"
#include <stdexcept>

std::string charABinario(char c) {
    std::string binario;
    for (int i = 7; i >= 0; i--) {
        binario += ((c >> i) & 1) ? '1' : '0';
    }
    return binario;
}

std::string textoABinario(const std::string& texto) {
    std::string binario;
    for (char c : texto) {
        binario += charABinario(c);
    }
    return binario;
}

char binarioAChar(const std::string& binario) {
    if (binario.length() != 8) {
        throw std::invalid_argument("Se necesitan exactamente 8 bits para un caracter");
    }

    char resultado = 0;
    for (int i = 0; i < 8; i++) {
        if (binario[i] == '1') {
            resultado |= (1 << (7 - i));
        }
    }
    return resultado;
}

std::string binarioATexto(const std::string& binario) {
    std::string texto;
    for (size_t i = 0; i < binario.length(); i += 8) {
        if (i + 8 <= binario.length()) {
            std::string byte = binario.substr(i, 8);
            texto += binarioAChar(byte);
        }
    }
    return texto;
}
