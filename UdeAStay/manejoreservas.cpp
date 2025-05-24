#include "manejoreservas.h"
#include <iostream>
#include <cstring>
#include <ctime>


using namespace std;


/*/void reservarAlojamiento(Usuario* usuario, Alojamiento** alojamientos, int totalAlojamientos, Reservas& reservas){
    int opcionBusqueda;
    cout << "\nOpciones de busqueda: " << endl;
    cout << "1. Por filros (fecha, municipio, noches, puntuacion)" << endl;
    cout << "2. Por codigo de alojamiento" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcionBusqueda;

    char fechaInicio[12], filtroCosto[3];
    int noches;
    float precioMin = 0.0, precioMax = 0.0;
    if(opcionBusqueda == 1){
        char municipio[50];
        cout << "Ingrese municipio: " << endl;
        cin >> municipio;
        cout << "Fecha de inicio (ej, 2025-02-22: " << endl;
        cin >> fechaInicio;
        cout << "Cantidad de noches: " << endl;
        cin >> noches;
        cout << "Desea aplicar un costo maximo y  minimo? (si o no): " << endl;
        cin >> filtroCosto;
        if(strcmp(filtroCosto, "si") == 0){
            cout << "\nIngrese precio minimo: ";
            cin >> precioMin;
            cout << "Ingrese precio maximo: ";
            cin >> precioMax;
        }
        cout << "\nAlojamientos Disponibles segun parametro:\n";
        bool encontrados = false;
        for(int i = 0; i < totalAlojamientos; ++i){
            Alojamiento* a = alojamientos[i];
            if(strcmp(a->getMunicipio(), municipio) != 0){
                continue;
            }
            if(precioMax > 0 && a->getPrecioPorNoche() > precioMax){
                continue;
            }
            if(precioMin > 0 && a->getPrecioPorNoche() < precioMin){
                continue;
            }
            if(!a->estaDisponible(fechaInicio,noches)){
                continue;
            }
            cout << i + 1 ;
            a->mostrarAlojamientos();
            encontrados = true;
        }
        if(!encontrados){
            cout << "No hay alojamientos que cumplan los filtros.\n";
            return;
        }
    }
}/*/
