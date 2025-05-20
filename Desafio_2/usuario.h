#ifndef USUARIO_H
#define USUARIO_H

class Usuario
{
private:
    char* nombreCompleto;
    char* documentoIdentidad;
    int mesesAntiguedad;
    float puntuacion;
public:
    Usuario();
    char* obtenerNombre();
    char* obtenerDocumento();
    float obtenerPuntuacion();
    void mostrarInformacion();
};

#endif // USUARIO_H
