#include "reservas.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

Reservas::Reservas() {
    capacidadReservas = 10;
    cantidadReservas = 0;
    listaReservas = new Reservacion*[capacidadReservas];
}

Reservas::~Reservas(){
    for(int i = 0; i < cantidadReservas; ++i){
        delete listaReservas[i];
    }
    delete[] listaReservas;
}

void Reservas::agregarReserva(Reservacion* nueva){
    if(cantidadReservas == capacidadReservas){
        int nuevaCapacidad = capacidadReservas * 2;
        Reservacion** nuevoArreglo = new Reservacion*[nuevaCapacidad];
        for(int i = 0; i < cantidadReservas; ++i){
            nuevoArreglo[i] = listaReservas[i];
        }
        delete[] listaReservas;
        listaReservas = nuevoArreglo;
        capacidadReservas = nuevaCapacidad;
    }
    listaReservas[cantidadReservas] = nueva;
    cantidadReservas += 1;
}

void Reservas::mostrarReservas() const {
    for(int i = 0; i < cantidadReservas; ++i){
        listaReservas[i]->mostrarReservacion();
    }
}

int Reservas::getCantidadReservas() const {
    return cantidadReservas;
}

Reservacion* Reservas::getlistaReservas(int idx) const{
    if(idx >= 0 && idx < cantidadReservas){
        return listaReservas[idx];
    }
    return nullptr;
}

void Reservas::cargarArchivoReservas(Usuario** usuarios, int totalUsuarios, Alojamiento** alojamientos, int totalAlojamientos){
    ifstream archivo("reservas.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios." << endl;
        return;
    }
    string linea;
    while(getline(archivo, linea)){
        size_t p1 = linea.find(',');
        size_t p2 = linea.find(',', p1 + 1);
        size_t p3 = linea.find(',', p2 + 1);
        size_t p4 = linea.find(',', p3 + 1);
        size_t p5 = linea.find(',', p4 + 1);
        size_t p6 = linea.find(',', p5 + 1);
        size_t p7 = linea.find(',', p6 + 1);
        size_t p8 = linea.find(',', p7 + 1);
        //size_t p9 = linea.find(',', p8 + 1);
        string fechaEntradaArchivo = linea.substr(0, p1);
        string noches = linea.substr(p1 + 1, p2 - p1 - 1);
        string codigoReservaArchivo = linea.substr(p2 + 1, p3 - p2 - 1);
        string codigoAlojamientoArchivo = linea.substr(p3 + 1, p4 - p3 - 1);
        string docHuespedArchivo = linea.substr(p4 + 1, p5 - p4 - 1);
        string metodoPagoArchivo = linea.substr(p5 + 1, p6 - p5 - 1);
        string fechaPagoArchivo = linea.substr(p6 + 1, p7 - p6 - 1);
        string monto = linea.substr(p7 + 1, p8 - p7 - 1);
        string anotacionesArchivo = linea.substr(p8 + 1);
        int nochesArchivo = atoi(noches.c_str());
        float montoArchivo = atof(monto.c_str());

        Usuario* huesped = nullptr;
        for(int i = 0; i < totalUsuarios; ++ i){
            if(strcmp(usuarios[i]->getDocumento(), docHuespedArchivo.c_str()) == 0 && usuarios[i]->esHuesped()){
                huesped = usuarios[i];
                break;
            }
        }

        Alojamiento* alojamiento = nullptr;
        for(int i = 0; i < totalAlojamientos; ++i){
            if(strcmp(alojamientos[i]->getCodigoAlojamiento(), codigoAlojamientoArchivo.c_str()) == 0){
                alojamiento = alojamientos[i];
                break;
            }
        }

        if(!fechaEntradaArchivo.empty() && !codigoReservaArchivo.empty() && alojamiento && huesped && !metodoPagoArchivo.empty() && !fechaPagoArchivo.empty()){
            Reservacion* reserva = new Reservacion(fechaEntradaArchivo.c_str(), nochesArchivo, codigoReservaArchivo.c_str(), alojamiento, huesped, metodoPagoArchivo.c_str(), fechaPagoArchivo.c_str(), montoArchivo, anotacionesArchivo.c_str());
            agregarReserva(reserva);
        }
    }
    archivo.close();
}
