#ifndef HUESPED_H
#define HUESPED_H

class Huesped
{
private:
    Reservacion** listaReservaciones;
    int cantidadReservaciones;
public:
    Huesped();
    bool tieneReserva(char* fechaIncio, int duracion);
    void crearReserva(Alojamiento* alojamiento, char* fechaIncio, int duracionNoches, char* metodoPago, char* fechaPago, float monto);
    void cancelarReserva(char* codigoReservacion);
};

#endif // HUESPED_H
