#ifndef USUARIO_H
#define USUARIO_H

class Usuario{
private:
    char nombreCompleto;
    char documentoIdentidad;
    int mesesAntiguedad;
    float puntuacion;
    char contraseña;
public:
    Usuario();
    Usuarios(const char*, const char*, int, float, const char*);

};

#endif // USUARIO_H
