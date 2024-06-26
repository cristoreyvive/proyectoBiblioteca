#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void login();
void agregarLibro();
void modificarLibro();
void eliminarLibro();

int main()
{
    login();

    int opcion;
    do
    {
        cout << "1. Agregar libro\n2. Modificar libro\n3. Eliminar libro\n4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            agregarLibro();
            break;
        case 2:
            modificarLibro();
            break;
        case 3:
            eliminarLibro();
            break;
        case 4:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 4);

    return 0;
}

void login()
{
    string username, password, stored_username, stored_password;
    cout << "Ingrese su nombre de usuario: ";
    cin >> username;
    cout << "Ingrese su contraseña: ";
    cin >> password;

    ifstream usersFile("bin/users.csv");
    if (usersFile.is_open())
    {
        while (usersFile >> stored_username >> stored_password)
        {
            if (username == stored_username && password == stored_password)
            {
                cout << "Inicio de sesión exitoso.\n";
                usersFile.close();
                return;
            }
        }
        cout << "Nombre de usuario o contraseña incorrectos.\n";
        usersFile.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios.\n";
    }
}

void agregarLibro()
{
    string titulo, autor;
    cout << "Ingrese el título del libro: ";
    cin.ignore();
    getline(cin, titulo);
    cout << "Ingrese el autor del libro: ";
    getline(cin, autor);

    ofstream librosFile("bin/libros.csv", ios::app);
    if (librosFile.is_open())
    {
        librosFile << titulo << "," << autor << "\n";
        librosFile.close();
        cout << "Libro agregado exitosamente.\n";
    }
    else
    {
        cout << "No se pudo abrir el archivo de libros.\n";
    }
}

void modificarLibro()
{
    string titulo, nuevoTitulo, nuevoAutor, linea;
    cout << "Ingrese el título del libro a modificar: ";
    cin.ignore();
    getline(cin, titulo);

    cout << "Ingrese el nuevo título del libro: ";
    getline(cin, nuevoTitulo);
    cout << "Ingrese el nuevo autor del libro: ";
    getline(cin, nuevoAutor);

    ifstream archivoEntrada("bin/libros.csv");
    ofstream archivoTemporal("bin/libros_temp.csv");

    if (archivoEntrada.is_open() && archivoTemporal.is_open())
    {
        bool encontrado = false;
        while (getline(archivoEntrada, linea))
        {
            size_t comaPos = linea.find(',');
            string tituloActual = linea.substr(0, comaPos);
            string autorActual = linea.substr(comaPos + 1);

            if (tituloActual == titulo)
            {
                archivoTemporal << nuevoTitulo << "," << nuevoAutor << "\n";
                encontrado = true;
            }
            else
            {
                archivoTemporal << linea << "\n";
            }
        }
        archivoEntrada.close();
        archivoTemporal.close();

        remove("bin/libros.csv");
        rename("bin/libros_temp.csv", "bin/libros.csv");

        if (encontrado)
        {
            cout << "Libro modificado exitosamente.\n";
        }
        else
        {
            cout << "Libro no encontrado.\n";
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo de libros.\n";
    }
}

void eliminarLibro()
{
    string titulo, linea;
    cout << "Ingrese el título del libro a eliminar: ";
    cin.ignore();
    getline(cin, titulo);

    ifstream archivoEntrada("bin/libros.csv");
    ofstream archivoTemporal("bin/libros_temp.csv");

    if (archivoEntrada.is_open() && archivoTemporal.is_open())
    {
        bool encontrado = false;
        while (getline(archivoEntrada, linea))
        {
            size_t comaPos = linea.find(',');
            string tituloActual = linea.substr(0, comaPos);

            if (tituloActual == titulo)
            {
                encontrado = true;
            }
            else
            {
                archivoTemporal << linea << "\n";
            }
        }
        archivoEntrada.close();
        archivoTemporal.close();

        remove("bin/libros.csv");
        rename("bin/libros_temp.csv", "bin/libros.csv");

        if (encontrado)
        {
            cout << "Libro eliminado exitosamente.\n";
        }
        else
        {
            cout << "Libro no encontrado.\n";
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo de libros.\n";
    }
}
