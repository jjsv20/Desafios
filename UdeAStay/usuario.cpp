#include "usuario.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

Usuario::Usuario(const char* nombreUsuario_, const char* documento_, char tipoRol_, int meses_, float puntuacion_) {
    nombreUsuario = new char[strlen(nombreUsuario_) + 1];
    strcpy(nombreUsuario, nombreUsuario_);
    documento = new char[strlen(documento_) + 1];
    strcpy(documento, documento_);
    tipoRol = tipoRol_;
    mesesAntiguedad = meses_;
    puntuacion = puntuacion_;
}

Usuario::~Usuario(){
    delete[] nombreUsuario;
    delete[] documento;
}

const char* Usuario::getNombreUsuario() const{
    return nombreUsuario;
}

char Usuario::getRol() const{
    return tipoRol;
}

const char* Usuario::getDocumento() const {
    return documento;
}

int Usuario::getMesesAntiguedad() const {
    return mesesAntiguedad;
}

float Usuario::getPuntuacion() const {
    return puntuacion;
}

bool Usuario::esHuesped() const {
    return tipoRol == 'H';
}

bool Usuario::esAnfitrion() const {
    return tipoRol == 'A';
}

Usuario* cargarUsuarioDesdeArchivo(const char* usuario, const char* documento) {
    ifstream archivo("usuarios.txt");
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
                punt
                );
        }
    }

    return nullptr;
}

