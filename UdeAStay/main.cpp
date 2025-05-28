#include "usuario.h"
#include "alojamiento.h"
#include "reservacion.h"
#include "sesion.h"
#include <iostream>

using namespace std;

void reservarAlojamiento(Usuario* huesped, Alojamiento** alojamientos, int totalAlojamientos, Reservacion**& reservas, int& totalReservas);
void anularReservas(Usuario* usuario, Reservacion**& reservas, int& totalReservas);

int main()
{
    Usuario** usuarios = 0;
    int totalUsuarios = 0;
    Usuario::cargarArchivoUsuarios(usuarios, totalUsuarios);

    Alojamiento** alojamientos = 0;
    int totalAlojamientos = 0;
    Alojamiento::cargarArchivoAlojamientos(alojamientos, totalAlojamientos, usuarios, totalUsuarios);

    Reservacion** reservas = 0;
    int totalReservas = 0;
    Reservacion::cargarReservas(reservas, totalReservas, usuarios, totalUsuarios, alojamientos, totalAlojamientos);
    Sesion sesion;
    while(true){
        int opcionPrincipal;
        cout << "\n -=-=-=-= UdeAStay -=-=-=-=" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;
        if(opcionPrincipal == 1){
            char nombreUsuario[20], documento[11];
            cout << "\nIngrese nombre de usuario: ";
            cin >> nombreUsuario;
            cout << "Ingrese documento: ";
            cin >> documento;
            if(!sesion.iniciarSesion(nombreUsuario, documento, usuarios, totalUsuarios)){
                cout << "Usuario no encontrado.\n";
                continue;
            }
            Usuario* usuario = sesion.getUsuarioActivo();
            cout << "\nBienvenido, " << usuario->getNombreUsuario() << endl;
            if(usuario->getRol() == 'H'){
                int opcionHuesped = 0;
                do {
                    cout << "\n--- Menú Huésped ---" << endl;
                    cout << "1. Reservar alojamiento" << endl;
                    cout << "2. Anular reservación" << endl;
                    cout << "3. Cerrar sesión" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> opcionHuesped;
                    switch (opcionHuesped) {
                    case 1:
                        reservarAlojamiento(usuario, alojamientos, totalAlojamientos, reservas, totalReservas);
                        break;
                    case 2:
                        anularReservas(usuario, reservas, totalReservas);
                        break;
                    case 3:
                        cout << "Cerrando sesión...\n";
                        break;
                    default:
                        cout << "Opción inválida.\n";
                    }
                } while (opcionHuesped != 3);
            } else if (usuario->getRol() == 'A') {
                cout << "Menú para anfitrión aún no implementado.\n";
                int opcionAnfitrion = 0;
                do {
                    cout << "\n--- Menú Anfitrión ---" << endl;
                    cout << "1. Consultar reservaciones" << endl;
                    cout << "2. Anular reservación" << endl;
                    cout << "3. Actualizar histórico" << endl;
                    cout << "4. Cerrar sesión" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> opcionAnfitrion;
                    switch (opcionAnfitrion) {
                    case 1:
                        cout << "Función para consultar reservaciones aún no implementada.\n";
                        break;
                    case 2:
                        cout << "Función para anular reservación aún no implementada.\n";
                        break;
                    case 3:
                        cout << "Función para actualizar histórico aún no implementada.\n";
                        break;
                    case 4:
                        cout << "Cerrando sesión...\n";
                        sesion.cerrarSesion();
                        break;
                    default:
                        cout << "Opción inválida.\n";
                    }
                } while (opcionAnfitrion != 4);
            }
        }else if(opcionPrincipal == 2){
            sesion.cerrarSesion();
            break;
        }
    }
    for (int i = 0; i < totalAlojamientos; ++i)
        delete alojamientos[i];
    delete[] alojamientos;

    for (int i = 0; i < totalUsuarios; ++i)
        delete usuarios[i];
    delete[] usuarios;
    return 0;
}
