#ifndef USUARIO_H
#define USUARIO_H

class Usuario
{
private:
    char* nombreUsuario;
    char* documento;
    char tipoRol;
    int mesesAntiguedad;
    float puntuacion;
public:
    Usuario(const char* nombreUsuario_, const char* documento_, char tipoRol_, int meses_, float puntuacion_);
    ~Usuario();
    const char* getNombreUsuario() const;
    char getRol() const;
    const char* getDocumento() const;
    int getMesesAntiguedad() const;
    float getPuntuacion() const;
    bool esHuesped() const;
    bool esAnfitrion() const;

    static void cargarArchivoUsuarios(Usuario**& usuarios, int& totalUsuarios);
    static Usuario* buscarUsuario(const char* usuario, const char* documento, Usuario** usuarios, int totalUsuarios);
};


#endif // USUARIO_H
