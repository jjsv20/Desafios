#ifndef RESERVACION_H
#define RESERVACION_H

#include "usuario.h"
#include "alojamiento.h"

class Reservacion
{
private:
    char* fechaEntrada;
    int duracion;
    char* codigoReservacaion;
    Alojamiento* alojamiento;
    Usuario* huesped;
    char* metodoDePago;
    char* fechadePago;
    float monto;
    char* anotaciones;
public:
    Reservacion(const char* fechaEntrada, int duracion, const char* codigoReservacaion, Alojamiento* alojamiento, Usuario* huesped, const char* metodoDePago, const char* fechadePago, float monto, const char* anotaciones);
    ~Reservacion();
    const char* getFechaEntrada();
    int getDuracion();
    const char* getCodigoReservacion();
    Alojamiento* getAlojamiento();
    Usuario* getHuesped();
    const char* getMetodoDePago();
    const char* getFechaDePago();
    float getMonto();
    const char* getAnotaciones();
};

#endif // RESERVACION_H
