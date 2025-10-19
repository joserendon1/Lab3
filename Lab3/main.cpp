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

std::string invertirBits(const std::string& bloque) {
    std::string resultado;
    for (char bit : bloque) {
        resultado += (bit == '0') ? '1' : '0';
    }
    return resultado;
}

std::string invertirCadaDosBits(const std::string& bloque) {
    std::string resultado = bloque;
    for (size_t i = 0; i + 1 < resultado.length(); i += 2) {
        char temp = resultado[i];
        resultado[i] = resultado[i + 1];
        resultado[i + 1] = temp;
    }
    return resultado;
}

std::string invertirCadaTresBits(const std::string& bloque) {
    std::string resultado = bloque;
    for (size_t i = 0; i + 2 < resultado.length(); i += 3) {
        char temp = resultado[i];
        resultado[i] = resultado[i + 2];
        resultado[i + 2] = temp;
    }
    return resultado;
}

std::string codificarMetodo1(const std::string& binario, int n) {
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

int main() {

    try {

        std::cout << "1. Probando con ejemplo 'AbCd' y n=4..." << std::endl;
        std::string texto = "AbCd";
        std::string binario = textoABinario(texto);
        std::string codificado = codificarMetodo1(binario, 4);

        std::cout << "Texto: " << texto << std::endl;
        std::cout << "Binario original: " << binario << std::endl;
        std::cout << "Binario codificado: " << codificado << std::endl;

        std::cout << "\n2. Verificando longitud..." << std::endl;
        std::cout << "Longitud original: " << binario.length() << " bits" << std::endl;
        std::cout << "Longitud codificado: " << codificado.length() << " bits" << std::endl;
        if (binario.length() == codificado.length()) {
            std::cout << "Longitudes coinciden: Si" << std::endl;
        } else {
            std::cout << "Longitudes coinciden: No" << std::endl;
            return 1;
        }

        std::cout << "\n3. Probando con archivo..." << std::endl;
        escribirArchivo("entrada.txt", "Test de codificacion");
        std::string contenido = leerArchivo("entrada.txt");
        binario = textoABinario(contenido);
        codificado = codificarMetodo1(binario, 5);
        escribirArchivo("salida_codificado.txt", codificado);
        std::cout << "Archivo codificado guardado como 'salida_codificado.txt'" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
