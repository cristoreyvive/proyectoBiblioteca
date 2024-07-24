#ifndef DATOS_H
#define DATOS_H

#include <string>
#include "Libro.h"
#include "Usuario.h"

using namespace std;

Libro *cargarLibros(int &numLibros);
Usuario *cargarUsuarios(int &numUsuarios);
void guardarLibros(Libro *libros, int numLibros);
void guardarUsuarios(Usuario *usuarios, int numUsuarios);
void registrarError(const string &mensaje);

#endif // DATOS_H
