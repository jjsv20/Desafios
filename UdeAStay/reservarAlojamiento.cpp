#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include "usuario.h"
#include "alojamiento.h"
#include "reservacion.h"
using namespace std;


//bool usuarioConReserva(const char* documento)

/*/void reservarAlojamiento(Usuario* huesped){
    int opcionBusqueda;
    cout << "\nOpciones de busqueda: " << endl;
    cout << "1. Por filros (fecha, municipio, noches, puntuacion)" << endl;
    cout << "2. Por codigo de alojamiento" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcionBusqueda;

    char fechaInicio[11], fechaFin[12];
    int noches;
    if(opcionBusqueda == 1){
        char municipio[50];
        cout << "Ingrese municipio: " << endl;
        cin >> municipio;
        cout << "Fecha de inicio (ej, 2025-02-22: " << endl;
        cin >> fechaInicio;
        cout << "Cantidad de noches: " << endl;
        cin >> noches;
        cout << "Desea aplicar un costo maximo y  minimo?" << endl;
    }
}/*/
