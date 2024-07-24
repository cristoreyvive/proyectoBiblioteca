#include "Datos.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;

void registrarError(const string &mensaje)
{
    cerr << "Error: " << mensaje << endl;
}

Libro *cargarLibros(int &numLibros)
{
    ifstream librosFile("libros.csv");
    if (!librosFile.is_open())
    {
        registrarError("No se pudo abrir el archivo de libros.");
        throw runtime_error("No se pudo abrir el archivo de libros.");
    }

    numLibros = 0;
    string line;
    while (getline(librosFile, line))
    {
        numLibros++;
    }
    librosFile.clear();
    librosFile.seekg(0, ios::beg);

    Libro *libros = new Libro[numLibros];
    int i = 0;
    while (getline(librosFile, line))
    {
        size_t pos = 0;
        size_t found = line.find(',');
        libros[i].titulo = line.substr(pos, found - pos);
        pos = found + 1;
        found = line.find(',', pos);
        libros[i].autor = line.substr(pos, found - pos);
        pos = found + 1;
        found = line.find(',', pos);
        libros[i].estado = line.substr(pos, found - pos);
        libros[i].compradoPor = line.substr(found + 1);
        i++;
    }

    librosFile.close();
    return libros;
}

Usuario *cargarUsuarios(int &numUsuarios)
{
    ifstream usersFile("users.csv");
    if (!usersFile.is_open())
    {
        registrarError("No se pudo abrir el archivo de usuarios.");
        throw runtime_error("No se pudo abrir el archivo de usuarios.");
    }

    numUsuarios = 0;
    string line;
    while (getline(usersFile, line))
    {
        numUsuarios++;
    }
    usersFile.clear();
    usersFile.seekg(0, ios::beg);

    Usuario *usuarios = new Usuario[numUsuarios];
    int i = 0;
    while (getline(usersFile, line))
    {
        size_t pos = 0;
        size_t found = line.find(',');
        usuarios[i].username = line.substr(pos, found - pos);
        pos = found + 1;
        found = line.find(',', pos);
        usuarios[i].password = line.substr(pos, found - pos);
        pos = found + 1;
        found = line.find(',', pos);
        usuarios[i].status = line.substr(pos, found - pos);
        usuarios[i].type = line.substr(found + 1);
        i++;
    }

    usersFile.close();
    return usuarios;
}

void guardarLibros(Libro *libros, int numLibros)
{
    ofstream librosFile("libros.csv");
    if (!librosFile.is_open())
    {
        registrarError("No se pudo abrir el archivo de libros para escritura.");
        throw runtime_error("No se pudo abrir el archivo de libros para escritura.");
    }

    for (int i = 0; i < numLibros; i++)
    {
        librosFile << libros[i].titulo << "," << libros[i].autor << "," << libros[i].estado << "," << libros[i].compradoPor << "\n";
    }

    librosFile.close();
}

void guardarUsuarios(Usuario *usuarios, int numUsuarios)
{
    ofstream usersFile("users.csv");
    if (!usersFile.is_open())
    {
        registrarError("No se pudo abrir el archivo de usuarios para escritura.");
        throw runtime_error("No se pudo abrir el archivo de usuarios para escritura.");
    }

    for (int i = 0; i < numUsuarios; i++)
    {
        usersFile << usuarios[i].username << "," << usuarios[i].password << "," << usuarios[i].status << "," << usuarios[i].type << "\n";
    }

    usersFile.close();
}
