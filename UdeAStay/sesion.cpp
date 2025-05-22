#include "sesion.h"
#include "usuario.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

Usuario* Sesion::iniciarSesion() {
    string usuario, documento;
    cout << "\nIngrese nombre de usuario: ";
    cin >> usuario;
    cout << "Ingrese documento: ";
    cin >> documento;
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return nullptr;
    }
    string linea;
    while (getline(archivo, linea)) {
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        size_t p3 = linea.find(',', p2 + 1);
        size_t p4 = linea.find(',', p3 + 1);
        string usuarioArchivo    = linea.substr(0, p1);
        string documentoArchivo  = linea.substr(p1 + 1, p2 - p1 - 1);
        string rolArchivo        = linea.substr(p2 + 1, p3 - p2 - 1);
        string mesesArchivo      = linea.substr(p3 + 1, p4 - p3 - 1);
        string puntuacionArchivo = linea.substr(p4 + 1);
        if (usuario == usuarioArchivo && documento == documentoArchivo) {
            char rol = rolArchivo[0];
            int meses = stoi(mesesArchivo);
            float punt = stof(puntuacionArchivo);
            return new Usuario(
                usuarioArchivo.c_str(),
                documentoArchivo.c_str(),
                rol,
                meses,
                punt);
        }
    }
    cout << "Usuario o documento incorrectos." << std::endl;
    return nullptr;
}

