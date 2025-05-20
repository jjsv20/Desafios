#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

class Alojamiento
{
private:
    char* codigoIdentificador;
    char* nombreAlojamiento;
    char* tipoAlojamiento;
    char* direccion;
    char* municipio;
    char* departamento;
    char* precioPorNoche;
    char** listaFechasReservadas;
    Anfitrion** anfitrionResponsable;
public:
    Alojamiento();
    bool estaDispobible(char* fechaInicio, int duracionNoches);
    void agregarReserva(char* fechaInicio, int duracionNoches);
    void mostrarInformacion();
    char* obtenerCodigoVerificador();
};

#endif // ALOJAMIENTO_H
