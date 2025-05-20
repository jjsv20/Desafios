#include <iostream>

using namespace std;

void menuPrincipal(){
    cout << "\n ===== UdeAStay ====" << endl;
    cout << "1. Iniciar sesion";
    cout << "2. Salir";
    cout << "Seleccione una opcion: ";
}

void menuHuesped(){
    cout << "\n--- Menu Huesped ---" << endl;
    cout << "1. Reservar alojamiento";
    cout << "2. Anular reservacion";
    cout << "3. Ver mis reservaciones";
    cout << "4. Cerrar sesion";
    cout << "Selecione una opcion: ";
}

void menuAnfitrion(){
    cout << "\n--- Menu Anfitrion ---" << endl;
    cout << "1. Consultar reservaciones";
    cout << "2. Anular reservacion";
    cout << "3. Actualizar historico";
    cout << "4. Cerrar sesion";
    cout << "Selecione una opcion: ";
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
