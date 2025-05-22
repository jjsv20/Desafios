#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include "usuario.h"
#include "alojamiento.h"
#include "reservacion.h"

//bool usuarioConReserva(const char* documento)

void reservarAlojamiento(Usuario* huesped){
    int opcionBusqueda;
    std::cout << "\nOpciones de busqueda: " << std::endl;
    std::cout << "1. Por filros (fecha, municipio, noches, puntuacion)" << std::endl;
    std::cout << "2. Por codigo de alojamiento" << std::endl;
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcionBusqueda;

    char fechaInicio[11], fechaFin[12];
    int noches;
    if(opcionBusqueda == 1){
        char municipio[50];
        std::cout << "Ingrese municipio: " << std::endl;
        std::cin >> municipio;
        std::cout << "Fecha de inicio (ej, 2025-02-22: " << std::endl;
        std::cin >> fechaInicio;
        std::cout << "Cantidad de noches: " << std::endl;
        std::cin >> noches;
        std::cout << "Desea aplicar un costo maximo y  minimo?" << std::endl;
    }
}
