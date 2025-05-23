#include <iostream>
#include <fstream>
#include <string>

#include "sesion.h"
#include "usuario.h"

using namespace std;

void menuHuesped(Usuario* usuario) {
    int opcionHuesped;
    do {
        cout << "\n--- Menú Huésped ---" << endl;
        cout << "1. Reservar alojamiento" << endl;
        cout << "2. Anular reservación" << endl;
        cout << "3. Mis reservaciones" << endl;
        cout << "4. Cerrar sesión" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcionHuesped;

        switch (opcionHuesped) {
        case 1:
            cout << "Función para reservar alojamiento aún no implementada.\n";
            break;
        case 2:
            cout << "Función para anular reservación aún no implementada.\n";
            break;
        case 3:
            cout << "Función para ver reservaciones aún no implementada.\n";
            break;
        case 4:
            cout << "Cerrando sesión...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }

    } while (opcionHuesped != 4);
}

void menuAnfitrion(Usuario* usuario) {
    int opcionAnfitrion;
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
            break;
        default:
            cout << "Opción inválida.\n";
        }

    } while (opcionAnfitrion != 4);
}

void menuPrincipal(Sesion& sesion){
    int opcionPrincipal;
    do {
        cout << "\n -=-=-=-= UdeAStay -=-=-=-=" << endl;
        cout << "1. Iniciar sesion" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;
        if(opcionPrincipal == 1){
            string nombreUsuario, documento;
            cout << "\nIngrese nombre de usuario: ";
            cin >> nombreUsuario;
            cout << "Ingrese documento: ";
            cin >> documento;
            if(sesion.iniciarSesion(nombreUsuario.c_str(), documento.c_str())){
                Usuario* usuario = sesion.getUsuarioActivo();
                cout << "\nBienvenido, " << usuario->getNombreUsuario() << endl;
                if(usuario->esHuesped()){
                    menuHuesped(usuario);
                }else if(usuario->esAnfitrion()){
                    menuAnfitrion(usuario);
                }else{
                    cout << "Usuario o documento incorrectos." << endl;
                }
                sesion.cerrarSesion();
            }else{
                cout << "Usuario o documento incorrectos." << endl;
            }
        }
    }while(opcionPrincipal != 2);
}

int main()
{
    Sesion sesion;
    menuPrincipal(sesion);
    return 0;
}
