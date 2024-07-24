#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

struct Libro
{
    string titulo;
    string autor;
    string estado;
    string compradoPor;
};

struct Usuario
{
    string username;
    string password;
    string status;
    string type;
};

Libro *cargarLibros(int &numLibros);
Usuario *cargarUsuarios(int &numUsuarios);
void guardarLibros(Libro *libros, int numLibros);
void guardarUsuarios(Usuario *usuarios, int numUsuarios);

void agregarLibro(Libro *&libros, int &numLibros);
void eliminarLibro(Libro *&libros, int &numLibros, const string &titulo);
void mostrarLibros(Libro *libros, int numLibros);
void modificarLibro(Libro *libros, int numLibros, const string &titulo);

bool iniciarSesion(Usuario *usuarios, int numUsuarios, string &username, string &userType);
void menuAdministrador(Libro *&libros, int &numLibros);
void menuEmpleado(Libro *&libros, int &numLibros);
void menuCliente(Libro *&libros, int numLibros, const string &username);

void registrarError(const string &mensaje);

int main()
{
    string userType, username;

    // Cargar datos en arreglos dinámicos
    int numLibros = 0, numUsuarios = 0;
    Libro *libros = nullptr;
    Usuario *usuarios = nullptr;

    try
    {
        libros = cargarLibros(numLibros);
        usuarios = cargarUsuarios(numUsuarios);
    }
    catch (const exception &e)
    {
        registrarError("Error al cargar datos: " + string(e.what()));
        return 1;
    }

    // Iniciar sesión
    try
    {
        if (!iniciarSesion(usuarios, numUsuarios, username, userType))
        {
            registrarError("Error de inicio de sesión para el usuario: " + username);
            cout << "Error de inicio de sesión.\n";
            return 1;
        }

        if (userType == "administrador")
        {
            menuAdministrador(libros, numLibros);
        }
        else if (userType == "empleado")
        {
            menuEmpleado(libros, numLibros);
        }
        else if (userType == "cliente")
        {
            menuCliente(libros, numLibros, username);
        }
    }
    catch (const exception &e)
    {
        registrarError("Error en el menú de usuario: " + string(e.what()));
        cout << "Error en el menú de usuario.\n";
    }

    // Guardar datos en archivos antes de salir
    try
    {
        guardarLibros(libros, numLibros);
        guardarUsuarios(usuarios, numUsuarios);
    }
    catch (const exception &e)
    {
        registrarError("Error al guardar datos: " + string(e.what()));
        cout << "Error al guardar datos.\n";
    }

    // Liberar memoria
    delete[] libros;
    delete[] usuarios;

    return 0;
}

Libro *cargarLibros(int &numLibros)
{
    ifstream librosFile("libros.csv");
    if (!librosFile.is_open())
    {
        registrarError("No se pudo abrir el archivo de libros.");
        throw runtime_error("No se pudo abrir el archivo de libros.");
    }

    // Contar el número de libros
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

    // Contar el número de usuarios
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

void agregarLibro(Libro *&libros, int &numLibros)
{
    Libro nuevoLibro;
    cout << "Ingrese el titulo del libro: ";
    cin.ignore();
    getline(cin, nuevoLibro.titulo);
    cout << "Ingrese el autor del libro: ";
    getline(cin, nuevoLibro.autor);
    nuevoLibro.estado = "disponible";
    nuevoLibro.compradoPor = "none";

    try
    {
        // Crear un nuevo arreglo dinámico con un libro más
        Libro *temp = new Libro[numLibros + 1];
        for (int i = 0; i < numLibros; i++)
        {
            temp[i] = libros[i];
        }
        temp[numLibros] = nuevoLibro;
        numLibros++;

        delete[] libros;
        libros = temp;

        cout << "Libro agregado exitosamente.\n";
    }
    catch (const exception &e)
    {
        registrarError("Error al agregar libro: " + string(e.what()));
        cout << "Error al agregar libro.\n";
    }
}

void eliminarLibro(Libro *&libros, int &numLibros, const string &titulo)
{
    int index = -1;
    for (int i = 0; i < numLibros; i++)
    {
        if (libros[i].titulo == titulo)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        registrarError("Error al eliminar libro: Libro no encontrado (" + titulo + ")");
        cout << "Libro no encontrado.\n";
        return;
    }

    try
    {
        // Crear un nuevo arreglo dinámico con un libro menos
        Libro *temp = new Libro[numLibros - 1];
        for (int i = 0, j = 0; i < numLibros; i++)
        {
            if (i != index)
            {
                temp[j++] = libros[i];
            }
        }
        numLibros--;

        delete[] libros;
        libros = temp;

        cout << "Libro eliminado exitosamente.\n";
    }
    catch (const exception &e)
    {
        registrarError("Error al eliminar libro: " + string(e.what()));
        cout << "Error al eliminar libro.\n";
    }
}

void mostrarLibros(Libro *libros, int numLibros)
{
    cout << "Lista de libros:\n";
    for (int i = 0; i < numLibros; i++)
    {
        cout << "Titulo: " << libros[i].titulo << ", Autor: " << libros[i].autor << ", Estado: " << libros[i].estado << ", Comprado por: " << libros[i].compradoPor << "\n";
    }
}

void modificarLibro(Libro *libros, int numLibros, const string &titulo)
{
    int index = -1;
    for (int i = 0; i < numLibros; i++)
    {
        if (libros[i].titulo == titulo)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        registrarError("Error al modificar libro: Libro no encontrado (" + titulo + ")");
        cout << "Libro no encontrado.\n";
        return;
    }

    int opcion;
    cout << "Qué desea modificar?\n";
    cout << "1. Título\n";
    cout << "2. Autor\n";
    cout << "3. Estado\n";
    cout << "Ingrese una opción: ";
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        cout << "Ingrese el nuevo título: ";
        cin.ignore();
        getline(cin, libros[index].titulo);
        break;
    case 2:
        cout << "Ingrese el nuevo autor: ";
        cin.ignore();
        getline(cin, libros[index].autor);
        break;
    case 3:
        cout << "Ingrese el nuevo estado (disponible/rented): ";
        cin.ignore();
        getline(cin, libros[index].estado);
        break;
    default:
        cout << "Opción inválida.\n";
        return;
    }
    cout << "Libro modificado exitosamente.\n";
}

bool iniciarSesion(Usuario *usuarios, int numUsuarios, string &username, string &userType)
{
    cout << "Ingrese su nombre de usuario: ";
    cin >> username;
    cout << "Ingrese su contraseña: ";
    string password;
    cin >> password;

    for (int i = 0; i < numUsuarios; i++)
    {
        if (usuarios[i].username == username && usuarios[i].password == password)
        {
            userType = usuarios[i].type;
            return true;
        }
    }
    return false;
}

void menuAdministrador(Libro *&libros, int &numLibros)
{
    int opcion;
    do
    {
        cout << "Menu Administrador:\n";
        cout << "1. Agregar libro\n";
        cout << "2. Modificar libro\n";
        cout << "3. Eliminar libro\n";
        cout << "4. Mostrar libros\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            agregarLibro(libros, numLibros);
            break;
        case 2:
        {
            string titulo;
            cout << "Ingrese el titulo del libro a modificar: ";
            cin.ignore();
            getline(cin, titulo);
            modificarLibro(libros, numLibros, titulo);
        }
        break;
        case 3:
        {
            string titulo;
            cout << "Ingrese el titulo del libro a eliminar: ";
            cin.ignore();
            getline(cin, titulo);
            eliminarLibro(libros, numLibros, titulo);
        }
        break;
        case 4:
            mostrarLibros(libros, numLibros);
            break;
        case 5:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
            break;
        }
    } while (opcion != 5);
}

void menuEmpleado(Libro *&libros, int &numLibros)
{
    int opcion;
    do
    {
        cout << "Menu Empleado:\n";
        cout << "1. Agregar libro\n";
        cout << "2. Eliminar libro\n";
        cout << "3. Mostrar libros\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            agregarLibro(libros, numLibros);
            break;
        case 2:
        {
            string titulo;
            cout << "Ingrese el titulo del libro a eliminar: ";
            cin.ignore();
            getline(cin, titulo);
            eliminarLibro(libros, numLibros, titulo);
        }
        break;
        case 3:
            mostrarLibros(libros, numLibros);
            break;
        case 4:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
            break;
        }
    } while (opcion != 4);
}

void menuCliente(Libro *&libros, int numLibros, const string &username)
{
    int opcion;
    do
    {
        cout << "Menu Cliente:\n";
        cout << "1. Mostrar libros\n";
        cout << "2. Rentar libro\n";
        cout << "3. Devolver libro\n";
        cout << "4. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            mostrarLibros(libros, numLibros);
            break;
        case 2:
        {
            string titulo;
            cout << "Ingrese el titulo del libro que desea rentar: ";
            cin.ignore();
            getline(cin, titulo);
            bool encontrado = false;
            for (int i = 0; i < numLibros; i++)
            {
                if (libros[i].titulo == titulo && libros[i].estado == "disponible")
                {
                    libros[i].estado = "rented";
                    libros[i].compradoPor = username;
                    encontrado = true;
                    cout << "Libro rentado exitosamente.\n";
                    break;
                }
            }
            if (!encontrado)
            {
                cout << "Libro no disponible o no encontrado.\n";
            }
        }
        break;
        case 3:
        {
            string titulo;
            cout << "Ingrese el titulo del libro que desea devolver: ";
            cin.ignore();
            getline(cin, titulo);
            bool encontrado = false;
            for (int i = 0; i < numLibros; i++)
            {
                if (libros[i].titulo == titulo && libros[i].compradoPor == username)
                {
                    libros[i].estado = "disponible";
                    libros[i].compradoPor = "none";
                    encontrado = true;
                    cout << "Libro devuelto exitosamente.\n";
                    break;
                }
            }
            if (!encontrado)
            {
                cout << "Libro no encontrado o no rentado por usted.\n";
            }
        }
        break;
        case 4:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
            break;
        }
    } while (opcion != 4);
}

void registrarError(const string &mensaje)
{
    ofstream logFile("error.log", ios::app);
    if (logFile.is_open())
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        logFile << 1900 + ltm->tm_year << "-"
                << 1 + ltm->tm_mon << "-"
                << ltm->tm_mday << " "
                << ltm->tm_hour << ":"
                << ltm->tm_min << ":"
                << ltm->tm_sec << " - "
                << mensaje << "\n";
        logFile.close();
    }
    else
    {
        cerr << "No se pudo abrir el archivo de log.\n";
    }
}
