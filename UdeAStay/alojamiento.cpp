#include "alojamiento.h"
#include <iostream>
#include <cstring>

using namespace std;

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
    fechasReservadas = new char*[totalFechas];
    for (int i = 0; i < totalFechas; ++i) {
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

void Alojamiento::cargarArchivoAlojamientos(){

}

void Alojamiento::mostrarAlojamientos() const{
    cout << "Nombre del alojamiento: " << nombreAlojamiento << endl;
    cout << "Codigo: " << codigoAlojamiento << endl;
    cout << "Ubicacion: " << municipio << ", " << departamento << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Precio por noche: " << precioPorNoche << endl;
    for(int i = 0; i < cantidadAmenidades; ++i){
        cout << (amenidades[i] ? amenidades[i] : "N/A");
        if(i < cantidadAmenidades - 1){
            cout << ", ";
        }
    }
}
