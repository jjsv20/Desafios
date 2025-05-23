#include "sesion.h"
#include "usuario.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

Sesion::Sesion(){
    usuarioActivo = nullptr;
}

Sesion::~Sesion(){
    delete usuarioActivo;
}

bool Sesion::iniciarSesion(const char* nombreUsuario, const char* documento){
    if(usuarioActivo != nullptr){
        cout << "Ya hay una sesión activa.\n";
        return false;
    }
    Usuario* encontrado = cargarUsuarioDesdeArchivo(nombreUsuario, documento);
    if(encontrado != nullptr){
        usuarioActivo = encontrado;
        return true;
    }else {
        cout << "Usuario o documento incorrectos." << endl;
        return false;
    }
}

void Sesion::cerrarSesion(){
    if(usuarioActivo){
        cout << "Sesión cerrada" << endl;
        delete usuarioActivo;
        usuarioActivo = nullptr;
    }else{
        cout << "No hay sesión activa." << endl;
    }
}

Usuario* Sesion::getUsuarioActivo() const {
    return usuarioActivo;
}
