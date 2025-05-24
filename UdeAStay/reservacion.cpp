#include "reservacion.h"
#include <cstring>
#include <iostream>

using namespace std;

Reservacion::Reservacion(const char* fechaEntrada_, int duracion_, const char* codigoReservacion_, Alojamiento* codigoAlojamiento_, Usuario* documentoHuesped_, const char* metodoDePago_, const char* fechadePago_, float monto_, const char* anotaciones_) {
    fechaEntrada = new char[strlen(fechaEntrada_) + 1];
    strcpy(fechaEntrada, fechaEntrada_);
    duracion = duracion_;
    codigoReservacion = new char[strlen(codigoReservacion_) + 1];
    strcpy(codigoReservacion, codigoReservacion_);
    codigoAlojamiento = new char[strlen(codigoAlojamiento_) + 1];
    strcpy(codigoAlojamiento, codigoAlojamiento_);
    documentoHuesped = new char[strlen(documentoHuesped_) + 1];
    strcpy(documentoHuesped, documentoHuesped_);
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
    delete[] codigoAlojamiento;
    delete[] documentoHuesped;
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

Alojamiento* Reservacion::getCodigoAlojamiento() const {
    return codigoAlojamiento;
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

void Reservacion::mostrarReservacion()const {
    cout << "Código de reservación: " << codigoReservacion << endl;
    cout << "Alojamiento: " << ;
    cout << "Huésped: ";
    if ('H') cout << documentoHuesped->getNombreUsuario() <<endl;
    cout << "Fecha de entrada: " << fechaEntrada << endl;
    cout << "Duración: " << duracion << " noches" << endl;
    cout << "Método de pago: " << metodoDePago << endl;
    cout << "Fecha de pago: " << fechadePago << endl;
    cout << "Monto: " << monto << endl;
    cout << "Anotaciones: " << anotaciones << endl;
}
