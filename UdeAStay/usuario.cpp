#include "usuario.h"
#include <cstring>

Usuario::Usuario(const char* nomUsua, const char* contra, char r, const char* doc, int meses, float p) {
    nombreUsuario = new char[strlen(nomUsua) + 1];
    strcpy(nombreUsuario, nomUsua);
    contraseña = new char[strlen(contra) + 1];
    strcpy(contraseña, contra);
    tipoRol = r;
    documento = doc;
    mesesAntiguedad = meses;
    puntuacion = p;
}

Usuario::~Usuario(){
    delete[] nombreUsuario;
    delete[] contraseña;
}

const char* Usuario::getNombreUsuario() const{
    return nombreUsuario;
}

const char* Usuario::getPassword() const{
    return contraseña;
}

const Usuario::getRol() const{
    return rol;
}
