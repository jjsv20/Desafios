#include "alojamiento.h"
#include "usuario.h"
#include "medicionmemoria.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

using namespace std;

void sumarDias(const char* fecha, int dias, char* resultado);

Alojamiento::Alojamiento(const char* nombreAlojamiento_, const char* codigoAlojamiento_, Usuario* anfitrion_, const char* departamento_, const char* municipio_, char tipo_, const char* direccion_, float precioPorNoche_, char** amenidades_, int cantidaAmenidades_, char** fechasReservadas_, int totalFechas_) {
    nombreAlojamiento = new char[strlen(nombreAlojamiento_) + 1];
    strcpy(nombreAlojamiento, nombreAlojamiento_);
    codigoAlojamiento = new char[strlen(codigoAlojamiento_) + 1];
    strcpy(codigoAlojamiento, codigoAlojamiento_);
    anfitrion = anfitrion_;
    departamento = new char[strlen(departamento_) + 1];
    strcpy(departamento, departamento_);
    municipio = new char[strlen(municipio_) + 1];
    strcpy(municipio, municipio_);
    tipo = tipo_;
    direccion = new char [strlen(direccion_) + 1];
    strcpy(direccion, direccion_);
    precioPorNoche = precioPorNoche_;
    cantidadAmenidades = cantidaAmenidades_;
    amenidades = new char*[cantidadAmenidades];
    for(int i = 0; i < cantidadAmenidades; ++i){
        amenidades[i] = new char[strlen(amenidades_[i]) + 1];
        strcpy(amenidades[i], amenidades_[i]);
    }
    totalFechas = totalFechas_;
    fechasReservadas = new char*[totalFechas_];
    for (int i = 0; i < totalFechas_; ++i) {
        fechasReservadas[i] = new char[strlen(fechasReservadas_[i]) + 1];
        strcpy(fechasReservadas[i], fechasReservadas_[i]);
    }
}

Alojamiento::~Alojamiento(){
    delete[] nombreAlojamiento;
    delete[] codigoAlojamiento;
    delete[] departamento;
    delete[] municipio;
    delete[] direccion;
    for(int i = 0; i < cantidadAmenidades; ++i){
        delete[] amenidades[i];
    }
    delete[] amenidades;
    for(int i = 0; i < totalFechas; ++i){
        delete[] fechasReservadas[i];
    }
    delete[] fechasReservadas;
}

const char* Alojamiento::getCodigoAlojamiento() const {
    return codigoAlojamiento;
}

const char* Alojamiento::getMunicipio() {
    return municipio;
}

float Alojamiento::getPrecioPorNoche() const {
    return precioPorNoche;
}

Usuario* Alojamiento::getAnfitrion() const {
    return anfitrion;
}

char** Alojamiento::getAmenidades() {
    return amenidades;
}

int Alojamiento::getCantidadAmenidades() const {
    return cantidadAmenidades;
}


bool Alojamiento::estaDisponible(const char* fechaInicio, int noches) const {
    char fechaActual[12];
    for(int i = 0; i < noches; ++i){
        ++iteraciones;
        sumarDias(fechaInicio, i, fechaActual);
        for(int j = 0; j < totalFechas; j += 2){
            if(j + 1 >= totalFechas){
                break;
            }
            const char* inicio = fechasReservadas[j];
            const char* fin = fechasReservadas[j + 1];
            if(strcmp(fechaActual, inicio) >= 0 && strcmp(fechaActual, fin) <= 0){
                return false;
            }
        }
    }
    return true;
}

void Alojamiento::cargarArchivoAlojamientos(Alojamiento**& alojamientos, int& totalAlojamientos, Usuario** usuarios, int totalUsuarios){
    ifstream archivo("alojamientos.txt");
    if (!archivo.is_open()) {
        //cout << "Error al abrir el archivo de usuarios." << endl;
        alojamientos = 0;
        totalAlojamientos = 0;
        return;
    }
    int capacidad = 10;
    totalAlojamientos = 0;
    alojamientos = new Alojamiento*[capacidad];
    string linea;
    while(getline(archivo, linea)){
        ++iteraciones;
        if(linea.empty() || linea[0] == '#'){
            continue;
        }
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        size_t p3 = linea.find(',', p2 + 1);
        size_t p4 = linea.find(',', p3 + 1);
        size_t p5 = linea.find(',', p4 + 1);
        size_t p6 = linea.find(',', p5 + 1);
        size_t p7 = linea.find(',', p6 + 1);
        size_t p8 = linea.find(',', p7 + 1);
        size_t p9 = linea.find(',', p8 + 1);
        string nombreAlojamiento = linea.substr(0, p1);
        string codigoAlojamiento = linea.substr(p1 + 1, p2 - p1 - 1);
        string nombreAnfitrion = linea.substr(p2 + 1, p3 - p2 - 1);
        string departamento = linea.substr(p3 + 1, p4 - p3 - 1);
        string municipio = linea.substr(p4 + 1, p5 - p4 - 1);
        char tipo = linea[p5 + 1];
        string direccion = linea.substr(p6 + 1, p7 - p6 - 1);
        float precioNoche = stof(linea.substr(p7 + 1, p8 - p7 - 1));
        string amenidadesAloja = linea.substr(p8 + 1, p9 - p8 - 1);
        string fechasAloja = linea.substr(p9 + 1);

        Usuario* anfitrion = 0;
        for (int i = 0; i < totalUsuarios; ++i){
            if(strcmp(usuarios[i]->getNombreUsuario(), nombreAnfitrion.c_str()) == 0){
                anfitrion = usuarios[i];
            }
        }

        int cantAmenidades = 0;
        char** amenidades = nullptr;
        {
            int count = 1;
            for(char c : amenidadesAloja){
                if(c == '.'){
                    count++;
                }
            }
            cantAmenidades = count;
            amenidades = new char*[cantAmenidades];
            int idx = 0;
            size_t pos = 0;
            while((pos = amenidadesAloja.find('.')) != string::npos){
                string temp = amenidadesAloja.substr(0, pos);
                amenidades[idx] = new char[temp.size() + 1];
                strcpy(amenidades[idx], temp.c_str());
                amenidadesAloja.erase(0, pos + 1);
                idx++;
            }
            amenidades[idx] = new char[amenidadesAloja.size() + 1];
            strcpy(amenidades[idx], amenidadesAloja.c_str());
        }

        int cantFechas = 1;
        char** fechas = nullptr;
        {
            int count = 1;
            for(char c : fechasAloja){
                if(c == '.'){
                    count++;
                }
            }
            cantFechas = count;
            fechas = new char*[cantFechas];
            int jdx = 0;
            size_t pos = 0;
            while((pos = fechasAloja.find('.')) != string::npos){
                string temp = fechasAloja.substr(0, pos);
                fechas[jdx] = new char[temp.size() + 1];
                strcpy(fechas[jdx], temp.c_str());
                fechasAloja.erase(0, pos + 1);
                jdx++;
            }
            fechas[jdx] = new char[fechasAloja.size() + 1];
            strcpy(fechas[jdx], fechasAloja.c_str());
        }

        if(totalAlojamientos >= capacidad){
            capacidad *= 2;
            Alojamiento** nuevo = new Alojamiento*[capacidad];
            for(int i = 0; i < totalAlojamientos; ++i){
                nuevo[i] = alojamientos[i];
            }
            delete[] alojamientos;
            alojamientos = nuevo;
        }
        alojamientos[totalAlojamientos++] = new Alojamiento(
            nombreAlojamiento.c_str(), codigoAlojamiento.c_str(), anfitrion,
            departamento.c_str(), municipio.c_str(), tipo,
            direccion.c_str(), precioNoche, amenidades, cantAmenidades, fechas, cantFechas
            );
        for (int j = 0; j < cantAmenidades; ++j){
            delete[] amenidades[j];
        }
        delete[] amenidades;
        for (int j = 0; j < cantFechas; ++j){
            delete[] fechas[j];
        }
        delete[] fechas;

    }
    archivo.close();
}
