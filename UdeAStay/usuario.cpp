#include "usuario.h"
#include <cstring>

Usuario::Usuario(const char* nombreUsuario_, const char* documento_, char tipoRol_, int meses_, float puntuacion_) {
    nombreUsuario = new char[strlen(nombreUsuario_) + 1];
    strncpy(nombreUsuario, nombreUsuario_, strlen(nombreUsuario_));
    documento = new char[strlen(documento_) + 1];
    strncpy(documento, documento_, strlen(documento_));
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
