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
    Alojamiento(const char* nombreAlojamiento, const char* codigoAlojamiento, Usuario* anfitrion, const char* departamento, const char* municipio, char tipo, const char* direccion, float precioPorNoche, char** amenidades, char** fechasReservadas, int totalFechas);

    ~Alojamiento();

    const char* getNombreAlojamiento();
    const char* getCodigoAlojamiento();
    Usuario* getAnfitrion();
    const char* getDepartamento();
    const char* getMunicipio();
    char getTipo() const;
    const char* getDireccion();
    float getPrecioPorNoche() const;
    const char** getAmenidades();

    bool estaDisponible(const char* fechaInicio, int noches);
    void mostrarAlojamientos();
};

#endif // ALOJAMIENTO_H
