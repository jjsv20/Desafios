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
    Usuario* documentoHuesped;
    char* metodoDePago;
    char* fechadePago;
    float monto;
    char* anotaciones;
    char* estado;
public:
    Reservacion(const char* fechaEntrada_, int duracion_, const char* codigoReservacion_, Alojamiento* alojamiento_, Usuario* documentoHuesped_, const char* metodoDePago_, const char* fechadePago_, float monto_, const char* anotaciones_, const char* estado_);
    ~Reservacion();
    const char* getFechaEntrada() const;
    int getDuracion() const;
    const char* getCodigoReservacion() const;
    Alojamiento* getAlojamiento() const;
    Usuario* getDocumentoHuesped() const;
    const char* getMetodoDePago() const;
    const char* getFechaDePago() const;
    float getMonto() const;
    const char* getAnotaciones() const;
    const char* getEstado() const;
    void setEstado(const char* nuevoEstado);  // <- LÍNEA AGREGADA
    static void cargarReservas(Reservacion**& reservas, int& total, Usuario** usuarios, int totalUsuarios, Alojamiento** alojamientos, int totalAlojamientos);
};
#endif // RESERVACION_H
