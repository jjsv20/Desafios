#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include "usuario.h"

class Alojamiento
{
private:
    char* nombreAlojamiento;
    char* codigoAlojamiento;
    Usuario* anfitrion;
    char* departamento;
    char* municipio;
    char tipo;
    char* direccion;
    float precioPorNoche;
    char** amenidades;
    int cantidadAmenidades;
    char** fechasReservadas;
    int totalFechas;
public:
    Alojamiento(const char* nombreAlojamiento_, const char* codigoAlojamiento_, Usuario* anfitrion_, const char* departamento_, const char* municipio_, char tipo_, const char* direccion_, float precioPorNoche_, char** amenidades_, int cantidadAmenidades_, char** fechasReservadas_, int totalFechas_);

    ~Alojamiento();

    const char* getNombreAlojamiento();
    const char* getCodigoAlojamiento() const;
    Usuario* getAnfitrion();
    const char* getDepartamento();
    const char* getMunicipio();
    char getTipo() const;
    const char* getDireccion();
    float getPrecioPorNoche() const;
    const char** getAmenidades();


    bool estaDisponible(const char* fechaInicio, int noches);
    void mostrarAlojamientos() const;
};

#endif // ALOJAMIENTO_H
