#include "Controlador.h"
#include "Datos.h"
#include <stdexcept>

Controlador::Controlador() : libros(nullptr), usuarios(nullptr), numLibros(0), numUsuarios(0)
{
    cargarDatos();
}

void Controlador::cargarDatos()
{
    try
    {
        libros = cargarLibros(numLibros);
        usuarios = cargarUsuarios(numUsuarios);
    }
    catch (const runtime_error &e)
    {
        vista.mostrarMensaje("Error al cargar datos: " + string(e.what()));
    }
}

void Controlador::guardarDatos()
{
    try
    {
        guardarLibros(libros, numLibros);
        guardarUsuarios(usuarios, numUsuarios);
    }
    catch (const runtime_error &e)
    {
        vista.mostrarMensaje("Error al guardar datos: " + string(e.what()));
    }
}

bool Controlador::iniciarSesion(string &username, string &userType)
{
    username = vista.pedirInput("Ingrese el nombre de usuario: ");
    string password = vista.pedirInput("Ingrese la contraseña: ");

    for (int i = 0; i < numUsuarios; ++i)
    {
        if (usuarios[i].username == username && usuarios[i].password == password)
        {
            userType = usuarios[i].type;
            return true;
        }
    }
    vista.mostrarMensaje("Nombre de usuario o contraseña incorrectos.");
    return false;
}

void Controlador::agregarLibro()
{
    Libro nuevoLibro;
    nuevoLibro.titulo = vista.pedirInput("Ingrese el título del libro: ");
    nuevoLibro.autor = vista.pedirInput("Ingrese el autor del libro: ");
    nuevoLibro.estado = "disponible";
    nuevoLibro.compradoPor = "none";

    try
    {
        Libro *temp = new Libro[numLibros + 1];
        for (int i = 0; i < numLibros; ++i)
        {
            temp[i] = libros[i];
        }
        temp[numLibros] = nuevoLibro;
        delete[] libros;
        libros = temp;
        ++numLibros;

        vista.mostrarMensaje("Libro agregado exitosamente.");
    }
    catch (const exception &e)
    {
        vista.mostrarMensaje("Error al agregar libro: " + string(e.what()));
    }
}

void Controlador::eliminarLibro()
{
    string titulo = vista.pedirInput("Ingrese el título del libro a eliminar: ");
    int index = -1;
    for (int i = 0; i < numLibros; ++i)
    {
        if (libros[i].titulo == titulo)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        vista.mostrarMensaje("Libro no encontrado.");
        return;
    }

    try
    {
        Libro *temp = new Libro[numLibros - 1];
        for (int i = 0, j = 0; i < numLibros; ++i)
        {
            if (i != index)
            {
                temp[j++] = libros[i];
            }
        }
        delete[] libros;
        libros = temp;
        --numLibros;

        vista.mostrarMensaje("Libro eliminado exitosamente.");
    }
    catch (const exception &e)
    {
        vista.mostrarMensaje("Error al eliminar libro: " + string(e.what()));
    }
}

void Controlador::modificarLibro()
{
    string titulo = vista.pedirInput("Ingrese el título del libro a modificar: ");
    int index = -1;
    for (int i = 0; i < numLibros; ++i)
    {
        if (libros[i].titulo == titulo)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        vista.mostrarMensaje("Libro no encontrado.");
        return;
    }

    int opcion = stoi(vista.pedirInput("Qué desea modificar?\n1. Título\n2. Autor\n3. Estado\nIngrese una opción: "));
    switch (opcion)
    {
    case 1:
        libros[index].titulo = vista.pedirInput("Ingrese el nuevo título: ");
        break;
    case 2:
        libros[index].autor = vista.pedirInput("Ingrese el nuevo autor: ");
        break;
    case 3:
        libros[index].estado = vista.pedirInput("Ingrese el nuevo estado (disponible/rented): ");
        break;
    default:
        vista.mostrarMensaje("Opción inválida.");
        return;
    }
    vista.mostrarMensaje("Libro modificado exitosamente.");
}

void Controlador::rentarLibro(const string &username)
{
    string titulo = vista.pedirInput("Ingrese el título del libro que desea rentar: ");
    bool encontrado = false;
    for (int i = 0; i < numLibros; ++i)
    {
        if (libros[i].titulo == titulo && libros[i].estado == "disponible")
        {
            libros[i].estado = "rented";
            libros[i].compradoPor = username;
            encontrado = true;
            vista.mostrarMensaje("Libro rentado exitosamente.");
            break;
        }
    }
    if (!encontrado)
    {
        vista.mostrarMensaje("Libro no disponible o no encontrado.");
    }
}

void Controlador::devolverLibro(const string &username)
{
    string titulo = vista.pedirInput("Ingrese el título del libro que desea devolver: ");
    bool encontrado = false;
    for (int i = 0; i < numLibros; ++i)
    {
        if (libros[i].titulo == titulo && libros[i].compradoPor == username)
        {
            libros[i].estado = "disponible";
            libros[i].compradoPor = "none";
            encontrado = true;
            vista.mostrarMensaje("Libro devuelto exitosamente.");
            break;
        }
    }
    if (!encontrado)
    {
        vista.mostrarMensaje("Libro no encontrado o no rentado por usted.");
    }
}

void Controlador::manejarAdministrador()
{
    while (true)
    {
        vista.mostrarMenuAdministrador();
        int opcion = vista.pedirOpcion();

        switch (opcion)
        {
        case 1: // Agregar libro
            agregarLibro();
            break;
        case 2: // Modificar libro
            modificarLibro();
            break;
        case 3: // Eliminar libro
            eliminarLibro();
            break;
        case 4: // Mostrar libros
            vista.mostrarLibros(libros, numLibros);
            break;
        case 5: // Salir
            guardarDatos();
            return;
        default:
            vista.mostrarMensaje("Opción no válida.");
            break;
        }
    }
}

void Controlador::manejarEmpleado()
{
    while (true)
    {
        vista.mostrarMenuEmpleado();
        int opcion = vista.pedirOpcion();

        switch (opcion)
        {
        case 1: // Agregar libro
            agregarLibro();
            break;
        case 2: // Eliminar libro
            eliminarLibro();
            break;
        case 3: // Mostrar libros
            vista.mostrarLibros(libros, numLibros);
            break;
        case 4: // Salir
            guardarDatos();
            return;
        default:
            vista.mostrarMensaje("Opción no válida.");
            break;
        }
    }
}

void Controlador::manejarCliente(const string &username)
{
    while (true)
    {
        vista.mostrarMenuCliente();
        int opcion = vista.pedirOpcion();

        switch (opcion)
        {
        case 1:
            vista.mostrarLibros(libros, numLibros);
            break;
        case 2: // Rentar libro
            rentarLibro(username);
            break;
        case 3: // Devolver libro
            devolverLibro(username);
            break;
        case 4: // Salir
            return;
        default:
            vista.mostrarMensaje("Opción no válida.");
            break;
        }
    }
}

void Controlador::ejecutar()
{
    while (true)
    {
        vista.mostrarMenuPrincipal();
        int opcion = vista.pedirOpcion();

        switch (opcion)
        {
        case 1: // Iniciar sesión
        {
            string username, userType;
            if (iniciarSesion(username, userType))
            {
                if (userType == "administrador")
                    manejarAdministrador();
                else if (userType == "empleado")
                    manejarEmpleado();
                else if (userType == "cliente")
                    manejarCliente(username);
            }
        }
        break;
        case 2: // Salir
            guardarDatos();
            return;
        default:
            vista.mostrarMensaje("Opción no válida.");
            break;
        }
    }
}
