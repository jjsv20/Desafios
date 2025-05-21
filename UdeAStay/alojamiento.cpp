#include "alojamiento.h"
#include <cstring>

Alojamiento::Alojamiento(const char* nombreA, const char* codigoA, Usuario* _anfitrion, const char* depa, const char* mun, char t, const char* direcc, float precio, char** amenids, char** fechas, int totalF) {
    nombreAlojamiento = new char[strlen(nombreA) + 1];
    strcpy(nombreAlojamiento, nombreA);
    codigoAlojamiento = new char[strlen(codigoA) + 1];
    strcpy(codigoAlojamiento, codigoA);
    anfitrion = _anfitrion;
    departamento = new char[strlen(depa) + 1];
    strcpy(departamento, depa);
    municipio = new char[strlen(mun) + 1];
    strcpy(municipio, mun);
    tipo = t;
    direccion = new char [strlen(direcc) + 1];
    strcpy(direccion, direcc);
    precioPorNoche = precio;
    cantidadAmenidades = 0;
    amenidades = new char*[cantidadAmenidades];
    for(int i = 0; i < cantidadAmenidades; ++i){
        amenidades[i] = new char[strlen(amenids[i]) + 1];
        strcpy(amenidades[i], amenids[i]);
    }
    totalFechas = totalF;
    fechasReservadas = new char*[totalFechas];
    for (int i = 0; i < totalFechas; ++i) {
        fechasReservadas[i] = new char[strlen(fechas[i]) + 1];
        strcpy(fechasReservadas[i], fechas[i]);
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

void Alojamiento::mostrarAlojamientos() const{

}
