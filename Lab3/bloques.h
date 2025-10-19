#ifndef BLOQUES_H
#define BLOQUES_H

#include <string>

std::string* dividirEnBloques(const std::string& binario, int n, int& numBloques);
std::string unirBloques(std::string* bloques, int numBloques);
int contarUnos(const std::string& bloque);

#endif
