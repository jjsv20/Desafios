#include "usuario.h"
#include <cstring>

Usuario::Usuario(const char* nomUsua, const char* contra, char r, const char* doc, int meses, float p) {
    nombreUsuario = new char[strlen(nomUsua) + 1];
    strncpy(nombreUsuario, nomUsua, strlen(nomUsua));
    contraseña = new char[strlen(contra) + 1];
    strncpy(contraseña, contra, strlen(contra));
    tipoRol = r;
    documento = new char[strlen(doc) + 1];
    strncpy(documento, doc, strlen(doc));
    mesesAntiguedad = meses;
    puntuacion = p;
}

Usuario::~Usuario(){
    delete[] nombreUsuario;
    delete[] contraseña;
    delete[] documento;
}

const char* Usuario::getNombreUsuario() const{
    return nombreUsuario;
}

const char* Usuario::getPassword() const{
    return contraseña;
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
