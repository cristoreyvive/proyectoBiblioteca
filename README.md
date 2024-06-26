# Sistema de Gestión de Biblioteca

Este proyecto es un sistema de gestión de biblioteca simple implementado en C++. Permite a los usuarios realizar diferentes acciones según su tipo de cuenta (administrador, empleado o cliente). Las acciones incluyen agregar, modificar y eliminar libros, así como agregar y gestionar usuarios y realizar transacciones de compra y devolución de libros.

## Funcionalidades

### Usuarios
- **Administrador:** Puede realizar todas las operaciones: agregar, modificar y eliminar libros, así como agregar, eliminar, suspender y reactivar usuarios.
- **Empleado:** Puede agregar, modificar y eliminar libros.
- **Cliente:** Puede comprar y devolver libros.

### Operaciones
- **Libros:**
  - Agregar un libro.
  - Modificar un libro existente.
  - Eliminar un libro.
- **Usuarios:**
  - Agregar un usuario nuevo.
  - Eliminar un usuario existente.
  - Suspender un usuario.
  - Quitar la suspensión de un usuario.
- **Transacciones:**
  - Comprar un libro.
  - Devolver un libro.

## Estructura del Código

- `main()`: Función principal que maneja el flujo del programa y muestra el menú de opciones.
- `login()`: Función que maneja el inicio de sesión de los usuarios.
- Funciones para la gestión de libros:
  - `agregarLibro()`
  - `modificarLibro()`
  - `eliminarLibro()`
- Funciones para la gestión de usuarios:
  - `agregarUsuario()`
  - `eliminarUsuario()`
  - `suspenderUsuario()`
  - `quitarSuspension()`
- Funciones para la gestión de transacciones:
  - `comprarLibro(const string &username)`
  - `devolverLibro(const string &username)`

## Archivos

- `users.csv`: Archivo donde se almacenan los datos de los usuarios (nombre de usuario, contraseña, estado y tipo de usuario).
- `libros.csv`: Archivo donde se almacenan los datos de los libros (título, autor, estado y comprador).

## Uso

### Compilación
Para compilar el programa, puedes usar un compilador de C++ como `g++`:

```sh
g++ -o biblioteca main.cpp

Iniciar Sesión
Al iniciar el programa, se te pedirá que ingreses tu nombre de usuario y contraseña. El sistema verificará tus credenciales y determinará tu tipo de usuario.

Menú Principal
Dependiendo de tu tipo de usuario, se te mostrarán diferentes opciones en el menú principal. Ingresa el número de la opción deseada y sigue las instrucciones en pantalla.


