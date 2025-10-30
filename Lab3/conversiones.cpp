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
    if (texto.empty()) {
        throw std::invalid_argument("Error: Texto vacio para convertir a binario");
    }

    std::string binario;
    for (size_t i = 0; i < texto.length(); i++) {
        binario += charABinario(texto[i]);
    }
    return binario;
}

char binarioAChar(const std::string& binario) {
    if (binario.length() != 8) {
        throw std::invalid_argument("Error: Se necesitan exactamente 8 bits para un caracter");
    }

    for (size_t i = 0; i < binario.length(); i++) {
        if (binario[i] != '0' && binario[i] != '1') {
            throw std::invalid_argument("Error: Cadena binaria contiene caracteres invalidos");
        }
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
    if (binario.empty()) {
        throw std::invalid_argument("Error: Binario vacio para convertir a texto");
    }

    if (binario.length() % 8 != 0) {
        throw std::invalid_argument("Error: Longitud de binario no es multiplo de 8");
    }

    std::string texto;
    for (size_t i = 0; i < binario.length(); i += 8) {
        std::string byte = binario.substr(i, 8);
        texto += binarioAChar(byte);
    }
    return texto;
}
