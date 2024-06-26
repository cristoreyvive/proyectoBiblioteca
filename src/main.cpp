#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void login();

int main()
{
    login();
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
                return;
            }
        }
        cout << "Nombre de usuario o contraseña incorrectos.\n";
    }
    else
    {
        cout << "No se pudo abrir el archivo de usuarios.\n";
    }
    usersFile.close();
}
