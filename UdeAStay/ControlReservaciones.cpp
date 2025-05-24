#include "usuario.h"
#include "alojamiento.h"
#include "reservacion.h"
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

bool esBisiesto(int año){
    return(año % 4 == 0 && año % 100 != 0) || (año % 400 == 0);
}

int diasDelMes(int mes, int año){
    switch(mes){
        case 2:
            return esBisiesto(año) ? 29 : 28;
        case 4: case 6: case 9: case 11:
            return 30;
        default: return 31;
    }
}

void fechaADigito(const char* fecha, int& dia, int& mes, int& año){
    sscanf(fecha, "%d-%d-%d", &dia, &mes, &año);
    if(año < 100){
        año += 2000;
    }
}

void sumarDias(const char* fecha, int dias, char* resultado){
    int dia, mes, año;
    fechaADigito(fecha, dia, mes, año);
    dia += dias;
    while(true){
        int diasMes = diasDelMes(mes, año);
        if(dia <= diasMes){
            break;
        }
        dia -= diasMes;
        mes++;
        if(mes > 12){
            mes += 1;
            año++;
        }
    }
    sprintf(resultado, "%02d-%02d-%02d", dia, mes, año);
}

const char* nombreDia(int dia, int mes, int año){
    if(mes < 3){
        mes += 12;
        año--;
    }
    int a = año % 100;
    int a_ = año /10;
    int d = (dia + 13*(mes + 1)/5 + a + a/4 + a_/4 + 5*a_) % 7;
    const char*dias[] = {"Sábado", "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes"};
    return dias[d];
}

const char* nombreMes(int mes){
    const char* meses[] = {"", "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
    return (mes >= 1 && mes <= 12) ? meses[mes] : "??";
}

void fechaATexto(const char* fecha){
    int dia, mes, año;
    fechaADigito(fecha, dia, mes, año);
    printf("%s, %d de %s del %d", nombreDia(dia, mes, año), dia, nombreMes(mes), año);
}

bool UsuarioConReservaEnFechas(Usuario* documentoHuesped, const char* fechaInicio, int noches, Reservacion** reservas, int totalReservas){
    char fechaReserva[12];
    strcpy(fechaReserva, fechaInicio);
    for(int i = 0; i < noches; ++i){
        for(int j = 0; j < totalReservas; ++j){
            Usuario* usuarioReserva = reservas[j]->getDocumentoHuesped();
            if(usuarioReserva && strcmp(usuarioReserva->getDocumento(), documentoHuesped->getDocumento()) == 0){
                int nocheExistente = reservas[j]->getDuracion();
                char FechaExistente[12];
                strcpy(FechaExistente, reservas[j]->getFechaEntrada());
                for(int k = 0; k < nocheExistente; ++k){
                    if(strcmp(FechaExistente, fechaReserva) == 0){
                        return true;
                    }
                    char fechaSiguiente[12];
                    sumarDias(FechaExistente, 1, fechaSiguiente);
                    strcpy(FechaExistente, fechaSiguiente);
                }
            }
        }
        char fechaSiguiente[12];
        sumarDias(fechaReserva, 1, fechaSiguiente);
        strcpy(fechaReserva, fechaSiguiente);
    }
    return false;
}

void reservarAlojamiento(Usuario* huesped, Alojamiento** alojamientos, int totalAlojamiento, Reservacion**& reservas, int& totalReservas){
    int opcionBusqueda;
    cout << "\nOpciones de busqueda: " << endl;
    cout << "1. Por filros (fecha, municipio, noches, puntuacion)" << endl;
    cout << "2. Por codigo de alojamiento" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcionBusqueda;
    char fechaInicio[12];
    int noches;
    float precioMin = 0.0, precioMax = 0.0, puntuacionMinima = 0.0;
    int idxAlojamiento = -1;
    if(opcionBusqueda == 1){
        char municipio[50];
        char filtroCosto[4];
        char filtroPuntuacion[4];
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
        //char filtroPuntuacion;
        cout << "Desea filtrar por puntuacion minima del anfitrion? (si o no): " << endl;
        cin >> filtroPuntuacion;
        if(strcmp(filtroPuntuacion, "si") == 0){
            cout << "\nIngrese precio minimo: ";
            cin >> puntuacionMinima;
        }

        int* indices = new int[totalAlojamiento];
        int alojamientosEncontrados = 0;
        for(int i = 0; i < totalAlojamiento; ++i){
            if(strcmp(alojamientos[i]->getMunicipio(), municipio) != 0){
                continue;
            }
            if(precioMax > 0 && alojamientos[i]->getPrecioPorNoche() > precioMax){
                continue;
            }
            if(puntuacionMinima > 0 && alojamientos[i]->getAnfitrion()->getPuntuacion() < puntuacionMinima){
                continue;
            }
            if(!alojamientos[i]->estaDisponible(fechaInicio, noches)){
                continue;
            }
            indices[alojamientosEncontrados] = i;
            alojamientosEncontrados++;
        }
        if(alojamientosEncontrados == 0){
            cout << "No se encontraron alojamientos para " << municipio << endl;
            delete[] indices;
            return;
        }
        cout << "\nAlojamientos disponibles en " << municipio << ": " << endl;
        for(int i  = 0; i < alojamientosEncontrados; ++i){
            cout << (i+1) << ". Codigo: " << alojamientos[indices[i]]->getCodigoAlojamiento()
                 << ", Precio: " << alojamientos[indices[i]]->getPrecioPorNoche()
                 << ", Puntuacion anfitrion: " << alojamientos[indices[i]]->getAnfitrion()->getPuntuacion() << endl;
        }
        cout << "Seleccione el codigo de alojamiento: ";
        int alojamientoSeleccionado;
        cin >> alojamientoSeleccionado;
        if(alojamientoSeleccionado < 0 || alojamientoSeleccionado >= alojamientosEncontrados){
            cout << "error";
            delete[] indices;
            return;
        }
        int idxAlojamientos = indices[alojamientoSeleccionado];
        delete[] indices;

        if(UsuarioConReservaEnFechas(huesped, fechaInicio, noches, reservas, totalReservas)){
            cout << "Ya tiene una reserva en esas fechas";
            return;
        }
        char metodoPago[10], fechaPago[12], anotaciones[1001];
        float monto = alojamientos[idxAlojamientos]->getPrecioPorNoche() * noches;
        cout << "Metodo de pago (PSE/Tarjeta de credito - 1 o 2): ";
        cin >> metodoPago;
        cout << "Fecha de pago (ej: 13-06-2025: ";
        cin >> fechaPago;
        cout << "Monto: ";
        cin >> monto;
        cin.ignore();
        cout << "Anotaciones: ";
        cin.getline(anotaciones,1000);
        char codReserva[20]; sprintf(codReserva, "RSV%04d", totalReservas+1);
        Reservacion* nuevaReservacion = new Reservacion(fechaInicio, noches, codReserva, alojamientos[idxAlojamientos], huesped, metodoPago, fechaPago, monto, anotaciones);
        Reservacion** tmp = new Reservacion*[totalReservas + 1];
        tmp[totalReservas] = nuevaReservacion;
        for(int i  = 0; i < totalReservas; ++i){
            tmp[i] = reservas[i];
        }
        tmp[totalReservas] = nuevaReservacion;
        delete[] reservas;
        reservas = tmp;
        ++totalReservas;
        char fechaFin[12];
        sumarDias(fechaInicio, noches - 1, fechaFin);
        cout << "\n---------------------------------------";
        cout << "\n Comprbante de Reservacion: " << endl;
        cout << "Codigo: " << codReserva << endl;
        cout << "Usuario: " << huesped->getNombreUsuario() << endl;
        cout << "Alojamiento: " << alojamientos[idxAlojamientos]->getCodigoAlojamiento() << endl;
        cout << "Fecha de entrada: "; fechaATexto(fechaInicio);
        cout << endl;
        cout << "Fecha de salida: "; fechaATexto(fechaFin);
        cout << endl;
        cout << "---------------------------------------";
    }else if(opcionBusqueda == 2){
        char codigoBuscado[5];
        cout << "Ingrese el código de alojamiento: ";
        cin >> codigoBuscado;
        cout << "Fecha de inicio (ej: 2025-02-22): ";
        cin >> fechaInicio;
        cout << "Cantidad de noches: ";
        cin >> noches;
        for(int i = 0; i < totalAlojamiento; ++i){
            if(strcmp(alojamientos[i]->getCodigoAlojamiento(), codigoBuscado) == 0){
                idxAlojamiento = i;
                break;
            }
        }
        if(idxAlojamiento == -1){
            std::cout << "No se encontró alojamiento con ese código.\n";
            return;
        }
        if(!alojamientos[idxAlojamiento]->estaDisponible(fechaInicio, noches)){
            std::cout << "El alojamiento no está disponible en esas fechas.\n";
            return;
        }
        if(UsuarioConReservaEnFechas(huesped, fechaInicio, noches, reservas, totalReservas)){
            std::cout << "Ya tiene una reserva en esas fechas.\n";
            return;
        }
        char metodoPago[10], fechaPago[12], anotaciones[1001];
        float monto = alojamientos[idxAlojamiento]->getPrecioPorNoche() * noches;
        cout << "Metodo de pago (PSE/Tarjeta de credito - 1 o 2): ";
        cin >> metodoPago;
        cout << "Fecha de pago (ej: 13-06-2025: ";
        cin >> fechaPago;
        cout << "Monto: ";
        cin >> monto;
        cin.ignore();
        cout << "Anotaciones: ";
        cin.getline(anotaciones,1000);
        char codReserva[20]; sprintf(codReserva, "RSV%04d", totalReservas+1);
        Reservacion* nuevaReservacion = new Reservacion(
            fechaInicio, noches, codReserva,
            alojamientos[idxAlojamiento], huesped,
            metodoPago, fechaPago, monto, anotaciones
            );
        Reservacion** tmp = new Reservacion*[totalReservas + 1];
        for(int i = 0; i < totalReservas; ++i){
            tmp[i] = reservas[i];
        }
        tmp[totalReservas] = nuevaReservacion;
        delete[] reservas;
        reservas = tmp;
        ++totalReservas;
        char fechaFin[12];
        sumarDias(fechaInicio, noches - 1, fechaFin);
        cout << "\n---------------------------------------";
        cout << "\n Comprbante de Reservacion: " << endl;
        cout << "Codigo: " << codReserva << endl;
        cout << "Usuario: " << huesped->getNombreUsuario();
        cout << "Alojamiento: " << alojamientos[idxAlojamiento]->getCodigoAlojamiento() << endl;
        cout << "Fecha de entrada: "; fechaATexto(fechaInicio);
        cout << endl;
        cout << "Fecha de salida: "; fechaATexto(fechaFin);
        cout << endl;
        cout << "---------------------------------------";
    }
    else{
        std::cout << "Opción no válida.\n";
        return;
    }
}
