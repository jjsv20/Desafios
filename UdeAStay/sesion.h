#ifndef SESION_H
#define SESION_H

#include "usuario.h"

class Sesion
{
private:
    Usuario* usuarioActivo;
public:
    Sesion();
    ~Sesion();

    bool iniciarSesion(const char* nombreUsuario, const char* documento, Usuario** usuarios, int totalUsuarios);
    void cerrarSesion();
    Usuario* getUsuarioActivo() const;
};

#endif // SESION_H
