#include <iostream>
#include <fstream>
#include <string>

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

bool iniciarSesion(Usuario *usuarios, int numUsuarios, string &username, string &userType);
void menuAdministrador(Libro *&libros, int &numLibros);
void menuEmpleado(Libro *&libros, int &numLibros);
void menuCliente(Libro *&libros, int numLibros, const string &username);

int main()
{
    string userType, username;

    // Cargar datos en arreglos dinámicos
    int numLibros = 0, numUsuarios = 0;
    Libro *libros = cargarLibros(numLibros);
    Usuario *usuarios = cargarUsuarios(numUsuarios);

    // Iniciar sesión
    if (!iniciarSesion(usuarios, numUsuarios, username, userType))
    {
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

    // Guardar datos en archivos antes de salir
    guardarLibros(libros, numLibros);
    guardarUsuarios(usuarios, numUsuarios);

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
        cout << "No se pudo abrir el archivo de libros.\n";
        return nullptr;
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
        cout << "No se pudo abrir el archivo de usuarios.\n";
        return nullptr;
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
        cout << "No se pudo abrir el archivo de libros.\n";
        return;
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
        cout << "No se pudo abrir el archivo de usuarios.\n";
        return;
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
        cout << "Libro no encontrado.\n";
        return;
    }

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

void mostrarLibros(Libro *libros, int numLibros)
{
    cout << "Lista de libros:\n";
    for (int i = 0; i < numLibros; i++)
    {
        cout << "Titulo: " << libros[i].titulo << ", Autor: " << libros[i].autor << ", Estado: " << libros[i].estado << ", Comprado Por: " << libros[i].compradoPor << "\n";
    }
}

bool iniciarSesion(Usuario *usuarios, int numUsuarios, string &username, string &userType)
{
    string user, pass;
    cout << "Ingrese su nombre de usuario: ";
    cin >> user;
    cout << "Ingrese su contraseña: ";
    cin >> pass;

    for (int i = 0; i < numUsuarios; i++)
    {
        if (usuarios[i].username == user && usuarios[i].password == pass)
        {
            username = user;
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
        cout << "2. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            mostrarLibros(libros, numLibros);
            break;
        case 2:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción inválida.\n";
            break;
        }
    } while (opcion != 2);
}
