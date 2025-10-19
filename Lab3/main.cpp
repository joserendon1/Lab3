#include <iostream>
#include <fstream>
#include <string>

std::string leerArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error: No se pudo abrir el archivo " + nombreArchivo);
    }

    std::string contenido;
    char caracter;
    while (archivo.get(caracter)) {
        contenido += caracter;
    }

    archivo.close();
    return contenido;
}

void escribirArchivo(const std::string& nombreArchivo, const std::string& contenido) {
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error: No se pudo crear el archivo " + nombreArchivo);
    }

    archivo << contenido;
    archivo.close();
}

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

int main() {

    try {

        std::cout << "1. Probando conversion de caracter 'A'..." << std::endl;
        std::string binarioA = charABinario('A');
        char caracterA = binarioAChar(binarioA);
        std::cout << "A -> binario: " << binarioA << " -> caracter: " << caracterA << std::endl;
        std::cout << "\n2. Probando conversion de texto 'Hola'..." << std::endl;
        std::string texto = "Hola";
        std::string binario = textoABinario(texto);
        std::string textoConvertido = binarioATexto(binario);
        std::cout << "Texto original: " << texto << std::endl;
        std::cout << "Texto convertido: " << textoConvertido << std::endl;
        std::cout << "Binario: " << binario << std::endl;
        std::cout << "\n3. Probando ida y vuelta..." << std::endl;
        std::string prueba = "AbCd123";
        std::string resultado = binarioATexto(textoABinario(prueba));
        if (prueba == resultado) {
            std::cout << "Conversion ida y vuelta exitosa" << std::endl;
        } else {
            std::cout << "Error en conversion ida y vuelta" << std::endl;
            return 1;
        }


    } catch (const std::exception& e) {
        std::cerr << "Error" << e.what() << std::endl;
        return 1;
    }

    return 0;
}
