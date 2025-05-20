#ifndef ANFITRION_H
#define ANFITRION_H

class Anfitrion
{
private:
    Alojamiento** listaAlojamientos;
    int cantidadAlojamientos;
public:
    Anfitrion();
    void agregarAlojamiento(Alojamiento* alojamiento);
    void mostrarReservasActivas(char* fechaInicio, char* fechaFin);
    void eliminarReservaporCodigo(chaar* codigoReservacion);
};

#endif // ANFITRION_H
