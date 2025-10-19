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

std::string* dividirEnBloques(const std::string& binario, int n, int& numBloques) {
    numBloques = (binario.length() + n - 1) / n;
    std::string* bloques = new std::string[numBloques];

    for (int i = 0; i < numBloques; i++) {
        int inicio = i * n;
        int longitud = n;
        if (inicio + longitud > binario.length()) {
            longitud = binario.length() - inicio;
        }
        bloques[i] = binario.substr(inicio, longitud);

        while (bloques[i].length() < n) {
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

int main() {
    std::cout << "=== FASE 3: Pruebas de Manipulacion de Bloques ===" << std::endl;

    try {

        std::cout << "1. Probando division en bloques..." << std::endl;
        std::string binario = "0100001011000100";
        int numBloques;
        std::string* bloques = dividirEnBloques(binario, 4, numBloques);

        std::cout << "Binario: " << binario << std::endl;
        std::cout << "Bloques de 4 bits: ";
        for (int i = 0; i < numBloques; i++) {
            std::cout << bloques[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "\n2. Probando union de bloques..." << std::endl;
        std::string unido = unirBloques(bloques, numBloques);
        std::cout << "Binario unido: " << unido << std::endl;
        if (binario == unido) {
            std::cout << "Coincide con original: Si" << std::endl;
        } else {
            std::cout << "Coincide con original: No" << std::endl;
            return 1;
        }

        std::cout << "\n3. Probando conteo de unos..." << std::endl;
        std::string bloquePrueba = "101001";
        int unos = contarUnos(bloquePrueba);
        std::cout << "Bloque: " << bloquePrueba << " -> Unos: " << unos << std::endl;
        if (unos == 3) {
            std::cout << "Conteo correcto" << std::endl;
        } else {
            std::cout << "Conteo incorrecto" << std::endl;
            return 1;
        }

        delete[] bloques;

    } catch (const std::exception& e) {
        std::cerr << "Error en Fase 3: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
