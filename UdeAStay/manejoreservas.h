#ifndef MANEJORESERVAS_H
#define MANEJORESERVAS_H

#include "usuario.h"
#include "alojamiento.h"
#include "reservas.h"

void reservarAlojamiento(Usuario* usuario, Alojamiento** alojamientos, int totalAlojamientos, Reservas& reservas);

#endif // MANEJORESERVAS_H
