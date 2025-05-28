#include "reservacion.h"
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

Reservacion::Reservacion(const char* fechaEntrada_, int duracion_, const char* codigoReservacion_, Alojamiento* alojamiento_, Usuario* documentoHuesped_, const char* metodoDePago_, const char* fechadePago_, float monto_, const char* anotaciones_) {
    fechaEntrada = new char[strlen(fechaEntrada_) + 1];
    strcpy(fechaEntrada, fechaEntrada_);
    duracion = duracion_;
    codigoReservacion = new char[strlen(codigoReservacion_) + 1];
    strcpy(codigoReservacion, codigoReservacion_);
    alojamiento = alojamiento_;
    //strcpy(codigoAlojamiento, codigoAlojamiento_);
    documentoHuesped = documentoHuesped_;
    //strcpy(documentoHuesped, documentoHuesped_);
    metodoDePago = new char[strlen(metodoDePago_) + 1];
    strcpy(metodoDePago, metodoDePago_);
    fechadePago = new char[strlen(fechadePago_) + 1];
    strcpy(fechadePago, fechadePago_);
    monto = monto_;
    anotaciones = new char[strlen(anotaciones_) + 1];
    strcpy(anotaciones, anotaciones_);
}

Reservacion::~Reservacion(){
    delete[] fechaEntrada;
    delete[] codigoReservacion;
    //delete[] codigoAlojamiento;
    //delete[] documentoHuesped;
    delete[] metodoDePago;
    delete[] fechadePago;
    delete[] anotaciones;
}

const char* Reservacion::getFechaEntrada() const {
    return fechaEntrada;
}

int Reservacion::getDuracion() const {
    return duracion;
}

const char* Reservacion::getCodigoReservacion() const {
    return codigoReservacion;
}

Alojamiento* Reservacion::getAlojamiento() const {
    return alojamiento;
}

Usuario* Reservacion::getDocumentoHuesped() const {
    return documentoHuesped;
}

const char* Reservacion::getMetodoDePago() const {
    return metodoDePago;
}

const char* Reservacion::getFechaDePago() const {
    return fechadePago;
}

float Reservacion::getMonto() const {
    return monto;
}

const char* Reservacion::getAnotaciones() const {
    return anotaciones;
}

void Reservacion::cargarReservas(Reservacion**& reservas, int& total, Usuario** usuarios, int totalUsuarios, Alojamiento** alojamientos, int totalAlojamientos) {
    ifstream archivo("reservas.txt");
    if (!archivo) {
        reservas = nullptr;
        total = 0;
        return;
    }
    int capacidad = 10;
    reservas = new Reservacion*[capacidad];
    total = 0;
    string linea;
    while(getline(archivo, linea)){
        if (linea.empty() || linea[0] == '#') continue;
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        size_t p3 = linea.find(',', p2 + 1);
        size_t p4 = linea.find(',', p3 + 1);
        size_t p5 = linea.find(',', p4 + 1);
        size_t p6 = linea.find(',', p5 + 1);
        size_t p7 = linea.find(',', p6 + 1);
        size_t p8 = linea.find(',', p7 + 1);

        if(p1 == string::npos || p2 == string::npos || p3 == string::npos || p4 == string::npos ||
            p5 == string::npos || p6 == string::npos || p7 == string::npos || p8 == string::npos) continue;

        string fechaEntradaArchivo = linea.substr(0, p1);
        string noches = linea.substr(p1 + 1, p2 - p1 - 1);
        string codigoReservaArchivo = linea.substr(p2 + 1, p3 - p2 - 1);
        string codigoAlojamientoArchivo = linea.substr(p3 + 1, p4 - p3 - 1);
        string docHuespedArchivo = linea.substr(p4 + 1, p5 - p4 - 1);
        string metodoPagoArchivo = linea.substr(p5 + 1, p6 - p5 - 1);
        string fechaPagoArchivo = linea.substr(p6 + 1, p7 - p6 - 1);
        string montoArchivo = linea.substr(p7 + 1, p8 - p7 - 1);
        string anotacionesArchivo = linea.substr(p8 + 1);

        int nochesArchivo = noches.empty() ? 0 : stoi(noches);
        float monto = montoArchivo.empty() ? 0 : atof(montoArchivo.c_str());

        // Buscar el huésped
        Usuario* huesped = nullptr;
        for(int i = 0; i < totalUsuarios; ++i){
            if(strcmp(usuarios[i]->getNombreUsuario(), docHuespedArchivo.c_str()) == 0 && usuarios[i]->esHuesped()){
                huesped = usuarios[i];
                break;
            }
        }
        // Buscar el alojamiento
        Alojamiento* alojamiento = nullptr;
        for(int i = 0; i < totalAlojamientos; ++i){
            if(strcmp(alojamientos[i]->getCodigoAlojamiento(), codigoAlojamientoArchivo.c_str()) == 0){
                alojamiento = alojamientos[i];
                break;
            }
        }
        if(huesped && alojamiento){
            if(total == capacidad){
                capacidad *= 2;
                Reservacion** temp = new Reservacion*[capacidad];
                for(int k = 0; k < total; ++k) temp[k] = reservas[k];
                delete[] reservas;
                reservas = temp;
            }
            reservas[total++] = new Reservacion(
                fechaEntradaArchivo.c_str(), nochesArchivo, codigoReservaArchivo.c_str(),
                alojamiento, huesped,
                metodoPagoArchivo.c_str(), fechaPagoArchivo.c_str(), monto, anotacionesArchivo.c_str()
                );
        }
    }
    archivo.close();
}
