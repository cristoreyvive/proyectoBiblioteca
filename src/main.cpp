#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool login();
void agregarLibro();
void modificarLibro();
void eliminarLibro();
void agregarUsuario();
void eliminarUsuario();
void suspenderUsuario();
void quitarSuspension();

int main()
{
    if (!login())
    {
        cout << "Inicio de sesión fallido. Saliendo del sistema.\n";
        return 1;
    }

    int opcion;
    do
    {
        cout << "1. Agregar libro\n2. Modificar libro\n3. Eliminar libro\n4. Agregar usuario\n5. Eliminar usuario\n6. Suspender usuario\n7. Quitar suspensión\n8. Salir\n";
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
            agregarUsuario();
            break;
        case 5:
            eliminarUsuario();
            break;
        case 6:
            suspenderUsuario();
            break;
        case 7:
            quitarSuspension();
            break;
        case 8:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opción no válida.\n";
        }
    } while (opcion != 8);

    return 0;
}

bool login()
{
    string username, password, stored_username, stored_password, status;
    cout << "Ingrese su nombre de usuario: ";
    cin >> username;
    cout << "Ingrese su contraseña: ";
    cin >> password;

    ifstream usersFile("users.csv");
    if (usersFile.is_open())
    {
        bool encontrado = false;
        while (getline(usersFile, stored_username, ',') && getline(usersFile, stored_password, ',') && getline(usersFile, status))
        {
            stored_username.erase(0, stored_username.find_first_not_of(" \t"));
            stored_username.erase(stored_username.find_last_not_of(" \t") + 1);
            stored_password.erase(0, stored_password.find_first_not_of(" \t"));
            stored_password.erase(stored_password.find_last_not_of(" \t") + 1);
            status.erase(0, status.find_first_not_of(" \t"));
            status.erase(status.find_last_not_of(" \t") + 1);

            if (username == stored_username && password == stored_password)
            {
                if (status == "suspendido")
                {
                    cout << "Su cuenta está suspendida. Acceso denegado.\n";
                    return false;
                }
                encontrado = true;
                break;
            }
        }
        usersFile.close();

        if (encontrado)
        {
            cout << "Inicio de sesión exitoso.\n";
            return true;
        }
        else
        {
            cout << "Nombre de usuario o contraseña incorrectos.\n";
            return false;
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios.\n";
        return false;
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

    ofstream librosFile("libros.csv", ios::app);
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

    ifstream archivoEntrada("libros.csv");
    ofstream archivoTemporal("libros_temp.csv");

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

        remove("libros.csv");
        rename("libros_temp.csv", "libros.csv");

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

    ifstream archivoEntrada("libros.csv");
    ofstream archivoTemporal("libros_temp.csv");

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

        remove("libros.csv");
        rename("libros_temp.csv", "libros.csv");

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

void agregarUsuario()
{
    string username, password;
    cout << "Ingrese el nombre de usuario: ";
    cin >> username;
    cout << "Ingrese la contraseña: ";
    cin >> password;

    ofstream usersFile("users.csv", ios::app);
    if (usersFile.is_open())
    {
        usersFile << username << "," << password << "\n";
        usersFile.close();
        cout << "Usuario agregado exitosamente.\n";
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios.\n";
    }
}

void eliminarUsuario()
{
    string username, linea;
    cout << "Ingrese el nombre de usuario a eliminar: ";
    cin.ignore();
    getline(cin, username);

    ifstream archivoEntrada("users.csv");
    ofstream archivoTemporal("users_temp.csv");

    if (archivoEntrada.is_open() && archivoTemporal.is_open())
    {
        bool encontrado = false;
        while (getline(archivoEntrada, linea))
        {
            size_t comaPos = linea.find(',');
            string usernameActual = linea.substr(0, comaPos);

            if (usernameActual == username)
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

        remove("users.csv");
        rename("users_temp.csv", "users.csv");

        if (encontrado)
        {
            cout << "Usuario eliminado exitosamente.\n";
        }
        else
        {
            cout << "Usuario no encontrado.\n";
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios.\n";
    }
}

void suspenderUsuario()
{
    string username, linea;
    cout << "Ingrese el nombre de usuario a suspender: ";
    cin.ignore();
    getline(cin, username);

    ifstream archivoEntrada("users.csv");
    ofstream archivoTemporal("users_temp.csv");

    if (archivoEntrada.is_open() && archivoTemporal.is_open())
    {
        bool encontrado = false;
        while (getline(archivoEntrada, linea))
        {
            size_t comaPos = linea.find(',');
            string usernameActual = linea.substr(0, comaPos);
            string resto = linea.substr(comaPos + 1);
            size_t comaPos2 = resto.find(',');
            string passwordActual = resto.substr(0, comaPos2);
            string estado = resto.substr(comaPos2 + 1);

            if (usernameActual == username)
            {
                archivoTemporal << usernameActual << "," << passwordActual << ",suspendido\n";
                encontrado = true;
            }
            else
            {
                archivoTemporal << linea << "\n";
            }
        }
        archivoEntrada.close();
        archivoTemporal.close();

        remove("users.csv");
        rename("users_temp.csv", "users.csv");

        if (encontrado)
        {
            cout << "Usuario suspendido exitosamente.\n";
        }
        else
        {
            cout << "Usuario no encontrado.\n";
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios.\n";
    }
}

void quitarSuspension()
{
    string username, linea;
    cout << "Ingrese el nombre de usuario al que desea quitarle la suspensión: ";
    cin.ignore();
    getline(cin, username);

    ifstream archivoEntrada("users.csv");
    ofstream archivoTemporal("users_temp.csv");

    if (archivoEntrada.is_open() && archivoTemporal.is_open())
    {
        bool encontrado = false;
        while (getline(archivoEntrada, linea))
        {
            size_t comaPos = linea.find(',');
            string usernameActual = linea.substr(0, comaPos);
            string resto = linea.substr(comaPos + 1);
            size_t comaPos2 = resto.find(',');
            string passwordActual = resto.substr(0, comaPos2);
            string estado = resto.substr(comaPos2 + 1);

            if (usernameActual == username)
            {
                archivoTemporal << usernameActual << "," << passwordActual << ",activo\n";
                encontrado = true;
            }
            else
            {
                archivoTemporal << linea << "\n";
            }
        }
        archivoEntrada.close();
        archivoTemporal.close();

        remove("users.csv");
        rename("users_temp.csv", "users.csv");

        if (encontrado)
        {
            cout << "Se ha quitado la suspensión al usuario exitosamente.\n";
        }
        else
        {
            cout << "Usuario no encontrado.\n";
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios.\n";
    }
}