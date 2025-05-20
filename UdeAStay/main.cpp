#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool iniciarSesion(string& nombreUsuario, string& tipoRol){
    string usuario, contraseña;
    cout << "\nIngrese nombre de usuario: ";
    cin >> usuario;
    cout << "Ingrese contraseña: ";
    cin >> contraseña;
    ifstream archivo("usuarios.txt");
    string linea;
    while(getline(archivo, linea)){
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        string usuarioArchivo = linea.substr(0, p1);
        string passwordArchivo = linea.substr(p1 + 1, p2 - p1 - 1);
        string rolArchivo = linea.substr(p2 + 1);
        if(usuario == usuarioArchivo && contraseña == passwordArchivo){
            tipoRol = rolArchivo;
            nombreUsuario = usuario;
            return true;
        }
    }
    cout << "Usuario o contraseña incorrectos.";
    return false;
}

int main()
{
    cout << "Hello World!" << endl;
    string usuario, rol;
    if(iniciarSesion(usuario, rol)){
        if(rol == "H"){
            cout << "Bienvenido " << usuario;
        }
    }
    return 0;
}
