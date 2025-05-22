#include "reservacion.h"
#include <cstring>
#include <iostream>

Reservacion::Reservacion(const char* fechaEntrada_, int duracion_, const char* codigoReservacion_, Alojamiento* alojamiento_, Usuario* huesped_, const char* metodoDePago_, const char* fechadePago_, float monto_, const char* anotaciones_) {
    fechaEntrada = new char[strlen(fechaEntrada_) + 1];
    strcpy(fechaEntrada, fechaEntrada_);
    duracion = duracion_;
    codigoReservacion = new char[strlen(codigoReservacion_) + 1];
    strcpy(codigoReservacion, codigoReservacion_);
    alojamiento = alojamiento_;
    huesped = huesped_;
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

void Reservacion::mostrarReservacion()const {
    std::cout << "Código de reservación: " << codigoReservacion << std::endl;
    std::cout << "Alojamiento: ";
    if (alojamiento) alojamiento->mostrarAlojamientos();
    std::cout << "Huésped: ";
    if (huesped) std::cout << huesped->getNombreUsuario() << std::endl;
    std::cout << "Fecha de entrada: " << fechaEntrada << std::endl;
    std::cout << "Duración: " << duracion << " noches" << std::endl;
    std::cout << "Método de pago: " << metodoDePago << std::endl;
    std::cout << "Fecha de pago: " << fechadePago << std::endl;
    std::cout << "Monto: " << monto << std::endl;
    std::cout << "Anotaciones: " << anotaciones << std::endl;
}
