#include "Vista.h"
#include <iostream>

void Vista::mostrarLibros(const Libro *libros, int numLibros)
{
    cout << "Lista de libros:\n";
    for (int i = 0; i < numLibros; i++)
    {
        cout << "Titulo: " << libros[i].titulo
             << ", Autor: " << libros[i].autor
             << ", Estado: " << libros[i].estado
             << ", Comprado por: " << libros[i].compradoPor << "\n";
    }
}

void Vista::mostrarMensaje(const string &mensaje)
{
    cout << mensaje << "\n";
}

void Vista::mostrarMenuAdministrador()
{
    cout << "Menu Administrador:\n";
    cout << "1. Agregar libro\n";
    cout << "2. Modificar libro\n";
    cout << "3. Eliminar libro\n";
    cout << "4. Mostrar libros\n";
    cout << "5. Salir\n";
}

void Vista::mostrarMenuEmpleado()
{
    cout << "Menu Empleado:\n";
    cout << "1. Agregar libro\n";
    cout << "2. Eliminar libro\n";
    cout << "3. Mostrar libros\n";
    cout << "4. Salir\n";
}

void Vista::mostrarMenuCliente()
{
    cout << "Menu Cliente:\n";
    cout << "1. Mostrar libros\n";
    cout << "2. Rentar libro\n";
    cout << "3. Devolver libro\n";
    cout << "4. Salir\n";
}

void Vista::mostrarMenuPrincipal()
{
    cout << "Menu Principal:\n";
    cout << "1. Iniciar sesión\n";
    cout << "2. Salir\n";
}

string Vista::pedirInput(const string &mensaje)
{
    string input;
    cout << mensaje;
    getline(cin, input);
    return input;
}

int Vista::pedirOpcion()
{
    int opcion;
    cin >> opcion;
    cin.ignore(); // Limpiar el buffer de entrada
    return opcion;
}
