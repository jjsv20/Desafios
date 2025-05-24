#ifndef RESERVAS_H
#define RESERVAS_H

#include "usuario.h"
#include "alojamiento.h"
#include "reservacion.h"

class Reservas
{
private:
    Reservacion** listaReservas;
    int cantidadReservas;
    int capacidadReservas;
public:
    Reservas();
    ~Reservas();

    void agregarReserva(Reservacion* nueva);
    void mostrarReservas() const;
    int getCantidadReservas() const;
    Reservacion* getlistaReservas(int idx) const;

    static void cargarArchivoReservas(Reservacion**& reservas, int& totalReservas, Usuario** usuarios, int totalUsuarios, Alojamiento** alojamientos, int totalAlojamientos);
};

#endif // RESERVAS_H
