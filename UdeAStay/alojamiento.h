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
    char* tipo;
    char* direccion;
    float precioPorNoche;
    char** amenidades;
    int cantidadAmenidades;
    char** fechasReservadas;
    int totalFechas;
public:
    Alojamiento(const char* nombreAlojamiento_, const char* codigoAlojamiento_, Usuario* anfitrion_, const char* departamento_, const char* municipio_, const char* tipo_, const char* direccion_, float precioPorNoche_, char** amenidades_, int cantidadAmenidades_, char** fechasReservadas_, int totalFechas_);

    ~Alojamiento();

    const char* getNombreAlojamiento();
    const char* getCodigoAlojamiento() const;
    Usuario* getAnfitrion() const;
    const char* getDepartamento();
    const char* getMunicipio();
    const char* getTipo();
    const char* getDireccion();
    char** getAmenidades();
    int getCantidadAmenidades() const;
    float getPrecioPorNoche() const;

    static void cargarArchivoAlojamientos(Alojamiento**& alojamientos, int& totalAlojamientos, Usuario** usuarios, int totalUsuarios);
    bool estaDisponible(const char* fechaInicio, int noches) const;
};

#endif // ALOJAMIENTO_H
