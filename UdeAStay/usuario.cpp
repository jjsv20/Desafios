#include "usuario.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

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

void Usuario::cargarArchivoUsuarios(Usuario**& usuarios, int& totalUsuarios) {
    ifstream archivo("usuarios.txt");
    if (!archivo) {
        usuarios = nullptr;
        totalUsuarios = 0;
        return;
    }
    int capacidad = 10; totalUsuarios = 0;
    usuarios = new Usuario*[capacidad];
    string linea;
    while (getline(archivo, linea)) {
        if(linea.empty() || linea[0] == '#'){
            continue;
        }
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        size_t p3 = linea.find(',', p2 + 1);
        size_t p4 = linea.find(',', p3 + 1);
        string usuarioArchivo = linea.substr(0, p1);
        string documentoArchivo = linea.substr(p1 + 1, p2 - p1 - 1);
        char rolArchivo = linea[p2 + 1];
        int mesesArchivo = stoi(linea.substr(p3 + 1, p4 - p3 - 1));
        float puntuacionArchivo = stof(linea.substr(p4 + 1));
        if(totalUsuarios == capacidad){
            capacidad *= 2;
            Usuario** temp = new Usuario*[capacidad];
            for(int i = 0; i < totalUsuarios; ++i){
                temp[i] = usuarios[i];
            }
            delete[] usuarios;
            usuarios = temp;
        }
        usuarios[totalUsuarios++] = new Usuario(usuarioArchivo.c_str(), documentoArchivo.c_str(), rolArchivo, mesesArchivo, puntuacionArchivo);
    }
    archivo.close();
}

Usuario* Usuario::buscarUsuario(const char* usuario, const char* documento, Usuario** usuarios, int totalUsuarios) {
    for(int i = 0; i < totalUsuarios; ++i){
        if(strcmp(usuarios[i]->getNombreUsuario(), usuario) == 0 && strcmp(usuarios[i]->getDocumento(), documento) == 0) {
            return usuarios[i];
        }
    }
    return nullptr;
}
