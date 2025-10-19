#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

std::string leerArchivo(const std::string& nombreArchivo);
void escribirArchivo(const std::string& nombreArchivo, const std::string& contenido);

#endif
