#include "reservacion.h"
#include <cstring>

Reservacion::Reservacion(const char* fechaEn, int durac, const char* codigoRese, Alojamiento* alojam, Usuario* huesp, const char* metodoP, const char* fechaP, float mont, const char* anota) {
    fechaEntrada = new char[strlen(fechaEn) + 1];
    strcpy(fechaEntrada, fechaEn);
    duracion = durac;
    codigoReservacaion = new char[strlen(codigoRese) + 1];
    strcpy(codigoReservacaion, codigoRese);
    alojamiento = alojam;
    huesped = huesp;
    metodoDePago = new char[strlen(metodoP) + 1];
    strcpy(metodoDePago, metodoDePago);
    fechadePago = new char[strlen(fechaP) + 1];
    strcpy(fechadePago, fechaP);
    monto = mont;
    anotaciones = new char[strlen(anota) + 1];
    strcpy(anotaciones, anota);
}

Reservacion::~Reservacion(){
    delete[] fechaEntrada;
    delete[] codigoReservacaion;
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

Usuario* Reservacion::getHuesped() const {
    return huesped;
}

const char* Reservacion::getMetodoPago() const {
    return metodoPago;
}

const char* Reservacion::getFechaPago() const {
    return fechaPago;
}

float Reservacion::getMonto() const {
    return monto;
}

const char* Reservacion::getAnotaciones() const {
    return anotaciones;
}
