#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "Vista.h"
#include "Datos.h"

class Controlador
{
private:
    Vista vista;
    Libro *libros;
    Usuario *usuarios;
    int numLibros;
    int numUsuarios;

    void cargarDatos();
    void guardarDatos();
    bool iniciarSesion(string &username, string &userType);
    void agregarLibro();
    void eliminarLibro();
    void modificarLibro();
    void rentarLibro(const string &username);
    void devolverLibro(const string &username);

    void manejarAdministrador();
    void manejarEmpleado();
    void manejarCliente(const string &username);

public:
    Controlador();
    void ejecutar();
};

#endif // CONTROLADOR_H
