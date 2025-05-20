#ifndef RESERVACION_H
#define RESERVACION_H

class Reservacion
{
private:
    char* codigoReservacion;
    Alojamiento* alojamientoReservado;
    Huesped* hespedAsociado;
    char* fechaInicioReserva;
    int duracionNoches;
    char* metodoPago;
    char* fechaPago;
    float montoPago;
public:
    Reservacion();
};

#endif // RESERVACION_H
