#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool login(string &userType, string &username);
void agregarLibro();
void modificarLibro();
void eliminarLibro();
void agregarUsuario();
void eliminarUsuario();
void suspenderUsuario();
void quitarSuspension();
void comprarLibro(const string &username);
void devolverLibro(const string &username);

int main()
{
    string userType, username;
    if (!login(userType, username))
    {
        cout << "Inicio de sesion fallido. Saliendo del sistema.\n";
        return 1;
    }

    int opcion;
    do
    {
        cout << "Menu:\n";
        if (userType == "administrador" || userType == "empleado")
        {
            cout << "1. Agregar libro\n2. Modificar libro\n3. Eliminar libro\n";
        }
        if (userType == "administrador")
        {
            cout << "4. Agregar usuario\n5. Eliminar usuario\n6. Suspender usuario\n7. Quitar suspension\n";
        }
        if (userType == "administrador" || userType == "cliente")
        {
            cout << "8. Comprar libro\n9. Devolver libro\n";
        }
        cout << "10. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            if (userType == "administrador" || userType == "empleado")
                agregarLibro();
            else
                cout << "Opcion no valida.\n";
            break;
        case 2:
            if (userType == "administrador" || userType == "empleado")
                modificarLibro();
            else
                cout << "Opcion no valida.\n";
            break;
        case 3:
            if (userType == "administrador" || userType == "empleado")
                eliminarLibro();
            else
                cout << "Opcion no valida.\n";
            break;
        case 4:
            if (userType == "administrador")
                agregarUsuario();
            else
                cout << "Opcion no valida.\n";
            break;
        case 5:
            if (userType == "administrador")
                eliminarUsuario();
            else
                cout << "Opcion no valida.\n";
            break;
        case 6:
            if (userType == "administrador")
                suspenderUsuario();
            else
                cout << "Opcion no valida.\n";
            break;
        case 7:
            if (userType == "administrador")
                quitarSuspension();
            else
                cout << "Opcion no valida.\n";
            break;
        case 8:
            if (userType == "administrador" || userType == "cliente")
                comprarLibro(username);
            else
                cout << "Opcion no valida.\n";
            break;
        case 9:
            if (userType == "administrador" || userType == "cliente")
                devolverLibro(username);
            else
                cout << "Opcion no valida.\n";
            break;
        case 10:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 10);

    return 0;
}

bool login(string &userType, string &username)
{
    string password, stored_username, stored_password, status, type;
    cout << "Ingrese su nombre de usuario: ";
    cin >> username;
    cout << "Ingrese su contraseña: ";
    cin >> password;

    ifstream usersFile("users.csv");
    if (usersFile.is_open())
    {
        while (getline(usersFile, stored_username, ',') && getline(usersFile, stored_password, ',') && getline(usersFile, status, ',') && getline(usersFile, type))
        {
            stored_username.erase(0, stored_username.find_first_not_of(" \t"));
            stored_username.erase(stored_username.find_last_not_of(" \t") + 1);

            if (username == stored_username && password == stored_password)
            {
                if (status == "suspendido")
                {
                    cout << "El usuario esta suspendido y tiene denegado el ingreso.\n";
                    return false;
                }
                cout << "Inicio de sesion exitoso.\n";
                userType = type;
                usersFile.close();
                return true;
            }
        }
        cout << "Nombre de usuario o contraseña incorrectos.\n";
        usersFile.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios.\n";
    }
    return false;
}

void agregarLibro()
{
    string titulo, autor;
    cout << "Ingrese el titulo del libro: ";
    cin.ignore();
    getline(cin, titulo);
    cout << "Ingrese el autor del libro: ";
    getline(cin, autor);

    ofstream librosFile("libros.csv", ios::app);
    if (librosFile.is_open())
    {
        librosFile << titulo << "," << autor << ",disponible,none\n";
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
    cout << "Ingrese el titulo del libro a modificar: ";
    cin.ignore();
    getline(cin, titulo);

    cout << "Ingrese el nuevo titulo del libro: ";
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
            string resto = linea.substr(comaPos + 1);
            size_t comaPos2 = resto.find(',');
            string autorActual = resto.substr(0, comaPos2);
            string estadoYCompradoPor = resto.substr(comaPos2 + 1);
            size_t comaPos3 = estadoYCompradoPor.find(',');
            string estado = estadoYCompradoPor.substr(0, comaPos3);
            string compradoPor = estadoYCompradoPor.substr(comaPos3 + 1);

            if (tituloActual == titulo)
            {
                archivoTemporal << nuevoTitulo << "," << nuevoAutor << "," << estado << "," << compradoPor << "\n";
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
    cout << "Ingrese el titulo del libro a eliminar: ";
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
    string username, password, type;
    cout << "Ingrese el nombre de usuario: ";
    cin >> username;
    cout << "Ingrese la contraseña: ";
    cin >> password;
    cout << "Ingrese el tipo de usuario (admin/empleado/cliente): ";
    cin >> type;

    ofstream usersFile("users.csv", ios::app);
    if (usersFile.is_open())
    {
        usersFile << username << "," << password << ",activo," << type << "\n";
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
            size_t comaPos1 = linea.find(',');
            string usernameActual = linea.substr(0, comaPos1);
            size_t comaPos2 = linea.find(',', comaPos1 + 1);
            string password = linea.substr(comaPos1 + 1, comaPos2 - comaPos1 - 1);
            size_t comaPos3 = linea.find(',', comaPos2 + 1);
            string status = linea.substr(comaPos2 + 1, comaPos3 - comaPos2 - 1);
            string type = linea.substr(comaPos3 + 1);

            if (usernameActual == username)
            {
                archivoTemporal << usernameActual << "," << password << ",suspendido," << type << "\n";
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
    cout << "Ingrese el nombre de usuario al que quiere quitar la suspension: ";
    cin.ignore();
    getline(cin, username);

    ifstream archivoEntrada("users.csv");
    ofstream archivoTemporal("users_temp.csv");

    if (archivoEntrada.is_open() && archivoTemporal.is_open())
    {
        bool encontrado = false;
        while (getline(archivoEntrada, linea))
        {
            size_t comaPos1 = linea.find(',');
            string usernameActual = linea.substr(0, comaPos1);
            size_t comaPos2 = linea.find(',', comaPos1 + 1);
            string password = linea.substr(comaPos1 + 1, comaPos2 - comaPos1 - 1);
            size_t comaPos3 = linea.find(',', comaPos2 + 1);
            string status = linea.substr(comaPos2 + 1, comaPos3 - comaPos2 - 1);
            string type = linea.substr(comaPos3 + 1);

            if (usernameActual == username)
            {
                archivoTemporal << usernameActual << "," << password << ",activo," << type << "\n";
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
            cout << "Suspension quitada exitosamente.\n";
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

void comprarLibro(const string &username)
{
    string titulo, linea;
    cout << "Ingrese el titulo del libro que desea comprar: ";
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
            string resto = linea.substr(comaPos + 1);
            size_t comaPos2 = resto.find(',');
            string autorActual = resto.substr(0, comaPos2);
            string estadoYCompradoPor = resto.substr(comaPos2 + 1);
            size_t comaPos3 = estadoYCompradoPor.find(',');
            string estado = estadoYCompradoPor.substr(0, comaPos3);
            string compradoPor = estadoYCompradoPor.substr(comaPos3 + 1);

            if (tituloActual == titulo && estado == "disponible")
            {
                archivoTemporal << tituloActual << "," << autorActual << ",comprado," << username << "\n";
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
            cout << "Libro comprado exitosamente.\n";
        }
        else
        {
            cout << "Libro no encontrado o no disponible.\n";
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo de libros.\n";
    }
}

void devolverLibro(const string &username)
{
    string titulo, linea;
    cout << "Ingrese el titulo del libro que desea devolver: ";
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
            string resto = linea.substr(comaPos + 1);
            size_t comaPos2 = resto.find(',');
            string autorActual = resto.substr(0, comaPos2);
            string estadoYCompradoPor = resto.substr(comaPos2 + 1);
            size_t comaPos3 = estadoYCompradoPor.find(',');
            string estado = estadoYCompradoPor.substr(0, comaPos3);
            string compradoPor = estadoYCompradoPor.substr(comaPos3 + 1);

            if (tituloActual == titulo && estado == "comprado" && compradoPor == username)
            {
                archivoTemporal << tituloActual << "," << autorActual << ",disponible,none\n";
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
            cout << "Libro devuelto exitosamente.\n";
        }
        else
        {
            cout << "Libro no encontrado o no comprado por usted.\n";
        }
    }
    else
    {
        cout << "No se pudo abrir el archivo de libros.\n";
    }
}