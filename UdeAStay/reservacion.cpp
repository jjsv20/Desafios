#include "reservacion.h"
#include <cstring>

Reservacion::Reservacion(const char* fechaEn, int durac, const char* codigoRese, Alojamiento* alojam, Usuario* huesp, const char* metodoP, const char* fechaP, float mont, const char* anota) {
    fechaEntrada = new char[strlen(fechaEn) + 1];
    strcpy(fechaEntrada, fechaEn);
    duracion = durac;
    codigoReservacion = new char[strlen(codigoRese) + 1];
    strcpy(codigoReservacion, codigoRese);
    alojamiento = alojam;
    huesped = huesp;
    metodoDePago = new char[strlen(metodoP) + 1];
    strcpy(metodoDePago, metodoP);
    fechadePago = new char[strlen(fechaP) + 1];
    strcpy(fechadePago, fechaP);
    monto = mont;
    anotaciones = new char[strlen(anota) + 1];
    strcpy(anotaciones, anota);
}

Reservacion::~Reservacion(){
    delete[] fechaEntrada;
    delete[] codigoReservacion;
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
