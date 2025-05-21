#include <iostream>
#include <fstream>
#include <string>

#include "sesion.h"
#include "usuario.h"

using namespace std;

void menuHuesped(){
    int opcionHuesped;
    do{
        cout << "\n Menu Huesped" << endl;
        cout << "\n1. Reservar alojamieto" << endl;
        cout << "2. Anular reservacion" << endl;
        cout << "3. Mis reservaciones" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "5. Seleccione una opcion: ";
        cin >> opcionHuesped;
    }while(opcionHuesped != 4);
}

void menuAnfitrion(){
    int opcionAnfitrion;
    do {
        cout << "\n Menu Anfitrion" << endl;
        cout << "1. Consultar reservaciones" << endl;
        cout << "2. Anular reservacion" << endl;
        cout << "3. Actualizar historico" << endl;
        cout << "4. Cerrar sesion" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcionAnfitrion;
    }while(opcionAnfitrion != 4);
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
            Usuario* usuario = sesion.iniciarSesion();
            if(usuario != nullptr){
                cout << "\nBienvenido, " << usuario->getNombreUsuario() << endl;
                if(usuario->getRol() == 'H'){
                    menuHuesped();
                }else if(usuario->getRol() == 'A'){
                    menuAnfitrion();
                }else{
                    cout << "Usuario no registrado";
                }
                delete usuario;
            }else{
                cout << "Usuario o contraseña invalidos";
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
