#ifndef RESERVACION_H
#define RESERVACION_H

#include "usuario.h"
#include "alojamiento.h"

class Reservacion
{
private:
    char* fechaEntrada;
    int duracion;
    char* codigoReservacion;
    Alojamiento* alojamiento;
    Usuario* huesped;
    char* metodoDePago;
    char* fechadePago;
    float monto;
    char* anotaciones;
public:
    Reservacion(const char* fechaEntrada_, int duracion_, const char* codigoReservacion_, Alojamiento* alojamiento_, Usuario* huesped_, const char* metodoDePago_, const char* fechadePago_, float monto_, const char* anotaciones_);
    ~Reservacion();
    const char* getFechaEntrada() const;
    int getDuracion() const;
    const char* getCodigoReservacion() const;
    Alojamiento* getAlojamiento() const;
    Usuario* getHuesped() const;
    const char* getMetodoDePago() const;
    const char* getFechaDePago() const;
    float getMonto() const;
    const char* getAnotaciones() const;

    void mostrarReservacion() const;
};

#endif // RESERVACION_H
