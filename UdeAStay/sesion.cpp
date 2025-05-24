#include "sesion.h"
#include "usuario.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

Sesion::Sesion(){
    usuarioActivo = 0;
}

Sesion::~Sesion(){
    usuarioActivo = 0;
}

bool Sesion::iniciarSesion(const char* nombreUsuario, const char* documento, Usuario** usuarios, int totalUsuarios){
    for(int i = 0; i < totalUsuarios; ++i){
        if(strcmp(usuarios[i]->getNombreUsuario(), nombreUsuario) == 0 && strcmp(usuarios[i]->getDocumento(), documento) == 0){
            usuarioActivo = usuarios[i];
            return true;
        }
    }
    return false;
}

void Sesion::cerrarSesion(){
    usuarioActivo = 0;
}

Usuario* Sesion::getUsuarioActivo() const {
    return usuarioActivo;
}
