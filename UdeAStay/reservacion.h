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
    Reservacion(const char* fechaEntrada, int duracion, const char* codigoReservacaion, Alojamiento* alojamiento, Usuario* huesped, const char* metodoDePago, const char* fechadePago, float monto, const char* anotaciones);
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
};

#endif // RESERVACION_H
