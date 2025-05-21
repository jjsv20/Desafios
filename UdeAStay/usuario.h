#ifndef USUARIO_H
#define USUARIO_H

class Usuario
{
private:
    char* nombreUsuario;
    char* contraseña;
    char tipoRol;
    char* documento;
    int mesesAntiguedad;
    float puntuacion;
public:
    Usuario(const char* nombreUsu, const char* password, char rol, const char* documento, int meses, float punt);
    ~Usuario();
    const char* getNombreUsuario() const;
    const char* getPassword() const;
    char getRol() const;
    const char* getDocumento() const;
    int getMesesAntiguedad() const;
    float getPuntuacion() const;
};

#endif // USUARIO_H
