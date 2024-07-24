#ifndef VISTA_H
#define VISTA_H

#include "Libro.h"
#include "Usuario.h"

class Vista
{
public:
    void mostrarLibros(const Libro *libros, int numLibros);
    void mostrarMensaje(const string &mensaje);
    void mostrarMenuAdministrador();
    void mostrarMenuEmpleado();
    void mostrarMenuCliente();
    void mostrarMenuPrincipal();
    string pedirInput(const string &mensaje);
    int pedirOpcion();
};

#endif // VISTA_H
