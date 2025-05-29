#include "usuario.h"
#include "alojamiento.h"
#include "reservacion.h"
#include "sesion.h"
#include "medicionmemoria.h"
#include <cstring>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

bool esBisiesto(int anio){
    return(anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int diasDelMes(int mes, int anio){
    switch(mes){
    case 2:
        return esBisiesto(anio) ? 29 : 28;
    case 4: case 6: case 9: case 11:
        return 30;
    default: return 31;
    }
}

void fechaADigito(const char* fecha, int& dia, int& mes, int& anio){
    sscanf(fecha, "%d-%d-%d", &dia, &mes, &anio);
    if(anio < 100){
        anio += 2000;
    }
}

void sumarDias(const char* fecha, int dias, char* resultado){
    int dia, mes, anio;
    fechaADigito(fecha, dia, mes, anio);
    dia += dias;
    while(true){
        int diasMes = diasDelMes(mes, anio);
        if(dia <= diasMes){
            break;
        }
        dia -= diasMes;
        mes++;
        if(mes > 12){
            mes = 1;
            anio++;
        }
    }
    sprintf(resultado, "%02d-%02d-%04d", dia, mes, anio);
}

int diaDeLaSemana(int dia, int mes, int anio){
    if(mes < 3){
        mes += 12;
        anio--;
    }
    int K = anio % 100;
    int J = anio / 100;
    int h = (dia + 13*(mes + 1)/5 + K + K/4 + J/4 + 5*J) % 7;
    return h;
}

const char* nombreDia(int dia, int mes, int anio){
    const char* dias[] = {"Sábado", "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes"};
    int idx = diaDeLaSemana(dia, mes, anio);
    return dias[idx];
}

const char* nombreMes(int mes){
    const char* meses[] = {"", "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
    return (mes >= 1 && mes <= 12) ? meses[mes] : "??";
}

void fechaATexto(const char* fecha){
    int dia, mes, anio;
    fechaADigito(fecha, dia, mes, anio);
    printf("%s, %d de %s del %d", nombreDia(dia, mes, anio), dia, nombreMes(mes), anio);
}


bool AlojamientoReservadoEnFechas(const char* codigoAlojamiento, const char* fechaInicio, int noches, Reservacion** reservas, int totalReservas) {
    char fechaReserva[12];
    strcpy(fechaReserva, fechaInicio);
    for(int i = 0; i < noches; ++i){
        ++iteraciones;
        for(int j = 0; j < totalReservas; ++j){
            ++iteraciones;
            if(strcmp(reservas[j]->getAlojamiento()->getCodigoAlojamiento(), codigoAlojamiento) == 0){
                int nochesExistentes = reservas[j]->getDuracion();
                char fechaExistente[12];
                strcpy(fechaExistente, reservas[j]->getFechaEntrada());
                for(int k = 0; k < nochesExistentes; ++k){
                    ++iteraciones;
                    if(strcmp(fechaExistente, fechaReserva) == 0){
                        return true; // Ya está reservado
                    }
                    char fechaSiguiente[12];
                    sumarDias(fechaExistente, 1, fechaSiguiente);
                    strcpy(fechaExistente, fechaSiguiente);
                }
            }
        }
        char fechaSiguiente[12];
        sumarDias(fechaReserva, 1, fechaSiguiente);
        strcpy(fechaReserva, fechaSiguiente);
    }
    return false;
}

bool UsuarioConReservaEnFechas(Usuario* documentoHuesped, const char* fechaInicio, int noches, Reservacion** reservas, int totalReservas){
    char fechaReserva[12];
    strcpy(fechaReserva, fechaInicio);
    for(int i = 0; i < noches; ++i){
        ++iteraciones;
        for(int j = 0; j < totalReservas; ++j){
            ++iteraciones;
            Usuario* usuarioReserva = reservas[j]->getDocumentoHuesped();
            if(usuarioReserva && strcmp(usuarioReserva->getDocumento(), documentoHuesped->getDocumento()) == 0){
                int nocheExistente = reservas[j]->getDuracion();
                char FechaExistente[12];
                strcpy(FechaExistente, reservas[j]->getFechaEntrada());
                for(int k = 0; k < nocheExistente; ++k){
                    ++iteraciones;
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

void agregarRangoFechaAlojamiento(const char* codigoAlojamiento, const char* fechaInicio, const char* fechaFin){
    ifstream archivo("alojamientos.txt");
    ofstream temporal("alojamientosTemp.txt");
    string linea;
    string codigoA(codigoAlojamiento);
    string fechaIniA(fechaInicio);
    string fechaFinA(fechaFin);

    while(getline(archivo, linea)){
        ++iteraciones;
        if(linea.find(codigoA) != string::npos){
            linea += "," + fechaIniA + "." + fechaFinA;
        }
        temporal << linea << "\n";
    }
    archivo.close();
    temporal.close();
    remove("alojamientos.txt");
    rename("alojamientosTemp.txt", "alojamientos.txt");
    cout << "exito";
}

void eliminarRangoFechaAlojamiento(const char* codigoAlojamiento, const char* fechaInicio, const char* fechaFin){
    ifstream archivo("alojamientos.txt");
    ofstream temporal("alojamientosTemp.txt");
    string linea;
    string codigoA(codigoAlojamiento);
    string rangoAEliminar = "," + string(fechaInicio) + "." + string(fechaFin);
    while(getline(archivo, linea)){
        ++iteraciones;
        if(linea.find(codigoA) != string::npos){
            size_t pos = linea.find(rangoAEliminar);
            if(pos != string::npos){
                linea.erase(pos, rangoAEliminar.length());
            }
        }
        temporal << linea << "\n";
    }
    archivo.close();
    temporal.close();
    remove("alojamientos.txt");
    rename("alojamientosTemp.txt", "alojamientos.txt");
    cout << "exito";
}

void CodigoReservacion(char* codigoGenerado){
    ifstream archivo("reservas.txt");
    string linea;
    int maximoCodigoReservacion = -1;
    while(getline(archivo, linea)){
        ++iteraciones;
        if (linea.empty() || linea[0] == '#') continue;
        stringstream ss(linea);
        string campos;
        int posicion = 0;
        while(getline(ss, campos, ',')){
            ++iteraciones;
            posicion++;
            if(posicion == 3 && campos.rfind("RSV", 0   ) == 0){
                int numero = stoi(campos.substr(3));
                if(numero > maximoCodigoReservacion){
                    maximoCodigoReservacion = numero;
                }
                break;
            }
        }
    }
    archivo.close();
    if(maximoCodigoReservacion == -1){
        maximoCodigoReservacion = 0;
    }else{
        maximoCodigoReservacion++;
    }
    sprintf(codigoGenerado, "RSV%04d", maximoCodigoReservacion);
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

    if(opcionBusqueda == 1){
        char municipio[50];
        char filtroCosto[4];
        char filtroPuntuacion[4];
        float precioMin = 0.0, precioMax = 0.0, puntuacionMinima = 0.0;
        cout << "\nIngrese municipio: ";
        cin >> municipio;
        cout << "Fecha de inicio (ej, 28-05-2025): ";
        cin >> fechaInicio;
        cout << "Cantidad de noches: ";
        cin >> noches;
        cout << "Desea aplicar un costo maximo y  minimo? (si o no): ";
        cin >> filtroCosto;
        if(strcmp(filtroCosto, "si") == 0){
            cout << "\nIngrese precio minimo: ";
            cin >> precioMin;
            cout << "Ingrese precio maximo: ";
            cin >> precioMax;
        }
        cout << "Desea filtrar por puntuacion minima del anfitrion? (si o no): ";
        cin >> filtroPuntuacion;
        if(strcmp(filtroPuntuacion, "si") == 0){
            cout << "\nIngrese puntuacion minima: ";
            cin >> puntuacionMinima;
        }

        int* indices = new int[totalAlojamiento];
        int alojamientosEncontrados = 0;
        for(int i = 0; i < totalAlojamiento; ++i){
            ++iteraciones;
            if(strcmp(alojamientos[i]->getMunicipio(), municipio) != 0){
                continue;
            }
            if(precioMax > 0 && alojamientos[i]->getPrecioPorNoche() > precioMax){
                continue;
            }
            Usuario* anfitrion = alojamientos[i]->getAnfitrion();
            if(puntuacionMinima > 0 && anfitrion != nullptr && anfitrion->getPuntuacion() < puntuacionMinima){
                continue;
            }
            if(!alojamientos[i]->estaDisponible(fechaInicio, noches)){
                continue;
            }
            indices[alojamientosEncontrados] = i;
            alojamientosEncontrados++;
        }
        if(alojamientosEncontrados == 0){
            cout << "\nNo se encontraron alojamientos para " << municipio << endl;
            delete[] indices;
            return;
        }
        cout << "\nAlojamientos disponibles en " << municipio << ": " << endl;
        for(int i  = 0; i < alojamientosEncontrados; ++i){
            ++iteraciones;
            int index = indices[i];
            Alojamiento* alojamiento = alojamientos[index];
            Usuario* anfitrion = alojamiento->getAnfitrion();
            cout << (i+1) << ". Codigo: " << alojamiento->getCodigoAlojamiento()
                 << ", Precio: " << alojamiento->getPrecioPorNoche();
            if (anfitrion != nullptr){
                cout << ", Puntuacion anfitrion: " << anfitrion->getPuntuacion();
            }else{
                cout << ", Puntuacion anfitrion: N/A";
            }
                cout << ", Amenidades: ";
            char** amenidades = alojamiento->getAmenidades();
            int cantidadAmenidades = alojamiento->getCantidadAmenidades();
            for(int j = 0; j < cantidadAmenidades; ++j){
                ++iteraciones;
                cout << amenidades[j];
                if(j < cantidadAmenidades - 1){
                    cout << ", ";
                }
            }
            cout << endl;
        }
        cout << "\nSeleccione el indice de alojamiento: ";
        int alojamientoSeleccionado;
        cin >> alojamientoSeleccionado;
        alojamientoSeleccionado--;
        if(alojamientoSeleccionado < 0 || alojamientoSeleccionado >= alojamientosEncontrados){
            cout << "\nIndice incorrecto";
            delete[] indices;
            return;
        }
        int idxAlojamiento = indices[alojamientoSeleccionado];
        delete[] indices;

        if (AlojamientoReservadoEnFechas(
                alojamientos[idxAlojamiento]->getCodigoAlojamiento(),
                fechaInicio, noches,
                reservas, totalReservas)) {
            cout << "\nEl alojamiento ya está reservado en esas fechas.\n";
            return;
        }

        if(UsuarioConReservaEnFechas(huesped, fechaInicio, noches, reservas, totalReservas)){
            cout << "\nYa tiene una reserva en esas fechas";
            return;
        }
        char metodoPago[20], fechaPago[12], anotaciones[1001];
        float monto = alojamientos[idxAlojamiento]->getPrecioPorNoche() * noches;
        char opcionPago[4];
        cout << "\nMetodo de pago (1.PSE/2.Tarjeta de credito): ";
        cin >> opcionPago;
        if(strcmp(opcionPago, "1") == 0) {
            strcpy(metodoPago, "PSE");
        } else if(strcmp(opcionPago, "2") == 0){
            strcpy(metodoPago, "Tarjeta de credito");
        } else {
            cout << "Método de pago no válido.\n";
            return;
        }
        cout << "Fecha de pago (ej: 13-06-2025): ";
        cin >> fechaPago;
        cout << "Anotaciones: ";
        cin.getline(anotaciones,1000);

        char codReserva[10];
        CodigoReservacion(codReserva);
        Reservacion* nuevaReservacion = new Reservacion(fechaInicio, noches, codReserva, alojamientos[idxAlojamiento], huesped, metodoPago, fechaPago, monto, anotaciones);
        Reservacion** tmp = new Reservacion*[totalReservas + 1];
        tmp[totalReservas] = nuevaReservacion;
        for(int i  = 0; i < totalReservas; ++i){
            ++iteraciones;
            tmp[i] = reservas[i];
        }
        tmp[totalReservas] = nuevaReservacion;
        delete[] reservas;
        reservas = tmp;
        ++totalReservas;
        char fechaFin[12];
        sumarDias(fechaInicio, noches - 1, fechaFin);
        cout << "\n---------------------------------------\n";
        cout << "\nComprobante de Reservacion: " << endl;
        cout << "Codigo: " << codReserva << endl;
        cout << "Usuario: " << huesped->getNombreUsuario() << endl;
        cout << "Alojamiento: " << alojamientos[idxAlojamiento]->getCodigoAlojamiento() << endl;
        cout << "Fecha de entrada: "; fechaATexto(fechaInicio);
        cout << endl;
        cout << "Fecha de salida: "; fechaATexto(fechaFin);
        cout << endl;
        cout << "Monto: $" << monto << " COP, por " << noches << " noches";
        cout << "\n---------------------------------------";
        char confirmarReserva[4];
        cout << "\n¿Desea confirmar la reservación? (si o no): ";
        cin >> confirmarReserva;
        if(strcmp(confirmarReserva, "si") == 0 || strcmp(confirmarReserva, "SI") == 0){
            agregarRangoFechaAlojamiento(alojamientos[idxAlojamiento]->getCodigoAlojamiento(), fechaInicio, fechaFin);
            ofstream archivo("reservas.txt", ios::app);
            if(archivo.is_open()){
                archivo << fechaInicio << ","
                        << noches << ","
                        << codReserva << ","
                        << alojamientos[idxAlojamiento]->getCodigoAlojamiento() << ","
                        << huesped->getNombreUsuario() << ","
                        << metodoPago << ","
                        << fechaPago << ","
                        << monto << ","
                        << anotaciones << endl;
                archivo.close();
                cout << "\nReserva confirmada exitosamente\n";
            }
        }else{
            cout << "\nReserva cancelada\n";
        }
    }else if(opcionBusqueda == 2){
        int idxAlojamiento = -1;
        char codigoBuscado[10];
        cout << "Ingrese el código de alojamiento: ";
        cin >> codigoBuscado;
        cout << "Fecha de inicio (ej: 2025-02-22): ";
        cin >> fechaInicio;
        cout << "Cantidad de noches: ";
        cin >> noches;
        for(int i = 0; i < totalAlojamiento; ++i){
            ++iteraciones;
            if(strcmp(alojamientos[i]->getCodigoAlojamiento(), codigoBuscado) == 0){
                idxAlojamiento = i;
                break;
            }
        }
        if(idxAlojamiento == -1){
            std::cout << "\nNo se encontró alojamiento con ese código.\n";
            return;
        }

        if (AlojamientoReservadoEnFechas(
                alojamientos[idxAlojamiento]->getCodigoAlojamiento(),
                fechaInicio, noches,
                reservas, totalReservas)) {
            cout << "\nEl alojamiento ya está reservado en esas fechas.\n";
            return;
        }

        if(!alojamientos[idxAlojamiento]->estaDisponible(fechaInicio, noches)){
            cout << "\nEl alojamiento no está disponible en esas fechas.\n";
            return;
        }
        if(UsuarioConReservaEnFechas(huesped, fechaInicio, noches, reservas, totalReservas)){
            cout << "\nYa tiene una reserva en esas fechas.\n";
            return;
        }
        char metodoPago2[10], fechaPago[12], anotaciones[1001];
        float monto = alojamientos[idxAlojamiento]->getPrecioPorNoche() * noches;
        char opcionPago2[4];
        cout << "\nMetodo de pago (1.PSE/2.Tarjeta de credito): ";
        cin >> opcionPago2;
        if(strcmp(opcionPago2, "1") == 0) {
            strcpy(metodoPago2, "PSE");
        } else if(strcmp(opcionPago2, "2") == 0){
            strcpy(metodoPago2, "Tarjeta de credito");
        } else {
            cout << "\nMétodo de pago no válido.\n";
            return;
        }
        cout << "Fecha de pago (ej: 13-06-2025): ";
        cin >> fechaPago;
        cin.ignore();
        cout << "Anotaciones: ";
        cin.getline(anotaciones,1000);
        char codReserva[10];
        CodigoReservacion(codReserva);
        Reservacion* nuevaReservacion = new Reservacion(fechaInicio, noches, codReserva, alojamientos[idxAlojamiento], huesped, metodoPago2, fechaPago, monto, anotaciones);
        Reservacion** tmp = new Reservacion*[totalReservas + 1];
        for(int i = 0; i < totalReservas; ++i){
            ++iteraciones;
            tmp[i] = reservas[i];
        }
        tmp[totalReservas] = nuevaReservacion;
        delete[] reservas;
        reservas = tmp;
        ++totalReservas;
        char fechaFin[12];
        sumarDias(fechaInicio, noches - 1, fechaFin);
        cout << "\n---------------------------------------\n";
        cout << "\nComprobante de Reservacion: ";
        cout << "Codigo: " << codReserva;
        cout << "Usuario: " << huesped->getNombreUsuario();
        cout << "Alojamiento: " << alojamientos[idxAlojamiento]->getCodigoAlojamiento() << endl;
        cout << "Fecha de entrada: "; fechaATexto(fechaInicio);
        cout << endl;
        cout << "Fecha de salida: "; fechaATexto(fechaFin);
        cout << endl;
        cout << "Monto: $" << monto << " COP, por " << noches << " noches";
        cout << "\n---------------------------------------";
        char confirmarReserva[4];
        cout << "\nDesea confirmar la reservacion? (si o no): ";
        cin >> confirmarReserva;
        if(strcmp(confirmarReserva, "si") == 0 || strcmp(confirmarReserva, "SI") == 0){
            agregarRangoFechaAlojamiento(alojamientos[idxAlojamiento]->getCodigoAlojamiento(), fechaInicio, fechaFin);
            std::ofstream archivo("reservas.txt", std::ios::app);
            if(archivo.is_open()){
                archivo << fechaInicio << ","
                        << noches << ","
                        << codReserva << ","
                        << alojamientos[idxAlojamiento]->getCodigoAlojamiento() << ","
                        << huesped->getNombreUsuario() << ","
                        << metodoPago2 << ","
                        << fechaPago << ","
                        << monto << ","
                        << anotaciones << endl;
                archivo.close();
                cout << "\nReserva confirmada exitosamente\n";
            }
        }else{
            cout << "\nRserva cancelada\n";
        }
    }
    else{
        cout << "Opción no válida.\n";
        return;
    }
}

void anularReservas(Usuario* usuario, Reservacion**& reservas, int& totalReservas) {
    if (totalReservas == 0) {
        cout << "\nNo hay reservas registradas.\n";
        return;
    }
    int contador = 0;
    for (int i = 0; i < totalReservas; ++i) {
        ++iteraciones;
        Usuario* usuarioReserva = reservas[i]->getDocumentoHuesped();
        if (usuarioReserva && strcmp(usuarioReserva->getNombreUsuario(), usuario->getNombreUsuario()) == 0) {
            char fechaFin[12];
            sumarDias(reservas[i]->getFechaEntrada(), reservas[i]->getDuracion() - 1, fechaFin);
            cout << "Reserva #" << (contador + 1) << endl;
            cout << "  Codigo: " << reservas[i]->getCodigoReservacion() << endl;
            cout << "  Alojamiento: " << reservas[i]->getAlojamiento()->getCodigoAlojamiento() << endl;
            cout << "  Fecha de entrada: ";
            fechaATexto(reservas[i]->getFechaEntrada());
            cout << endl;
            cout << "  Fecha de salida: ";
            fechaATexto(fechaFin);
            cout << endl;
            cout << "  Cantidad de noches: " << reservas[i]->getDuracion() << endl;
            cout << "  Metodo de pago: " << reservas[i]->getMetodoDePago() << endl;
            cout << "  Fecha de pago: " << reservas[i]->getFechaDePago() << endl;
            cout << "  Monto: " << reservas[i]->getMonto() << endl;
            cout << "  Anotaciones: " << reservas[i]->getAnotaciones() << endl;
            cout << "-----------------------------\n";
            ++contador;
        }
    }
    if (contador == 0) {
        cout << "\nActualmente te encuntras sin reserevaciones\n";
        return;
    }
    char codigoAEliminar[15];
    cout << "\nSeleccione el codigo de la reserva a eliminar (ejemplo: RS001): ";
    cin >> codigoAEliminar;

    int idxCodigo = -1;
    for(int i = 0; i < totalReservas; ++i){
        ++iteraciones;
        Usuario* reservasUsuario = reservas[i]->getDocumentoHuesped();
        if(reservasUsuario && strcmp(reservasUsuario->getNombreUsuario(), usuario->getNombreUsuario()) == 0 && strcmp(reservas[i]->getCodigoReservacion(), codigoAEliminar) == 0){
            idxCodigo = i;
            break;
        }
    }
    if (idxCodigo == -1) {
        cout << "No se encontró una reserva con ese código.\n";
        return;
    }
    char confirmarEliminacion[6];
    cout << "\nEsta seguro de eliminar la reservacion " << codigoAEliminar << "? (si o no): ";
    cin >> confirmarEliminacion;
    if(strcmp(confirmarEliminacion, "si") == 0 || strcmp(confirmarEliminacion, "SI") == 0){
        const char* codigoAlojamiento = reservas[idxCodigo]->getAlojamiento()->getCodigoAlojamiento();
        const char* fechaInicio      = reservas[idxCodigo]->getFechaEntrada();
        int noches                  = reservas[idxCodigo]->getDuracion();
        char fechaFin[12];
        sumarDias(fechaInicio, noches - 1, fechaFin);
        eliminarRangoFechaAlojamiento(codigoAlojamiento, fechaInicio, fechaFin);
        Reservacion* reservaEliminada = reservas[idxCodigo];
        Reservacion** tmp = new Reservacion*[totalReservas - 1];
        int idxTmp = 0;
        for (int i = 0; i < totalReservas; ++i) {
            if (i != idxCodigo) {
                tmp[idxTmp++] = reservas[i];
            }
        }
        delete reservaEliminada;
        delete[] reservas;
        reservas = tmp;
        --totalReservas;
        ifstream archivo("reservas.txt");
        ofstream temporal("reserva_temp.txt");
        string linea;
        while (getline(archivo, linea)) {
            if (linea.empty() || linea[0] == '#'){
                temporal << linea << "\n";
                continue;
            }
            size_t pos1 = linea.find(',');
            size_t pos2 = linea.find(',', pos1 + 1);
            size_t pos3 = linea.find(',', pos2 + 1);
            string codArchivo = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            if (codArchivo != codigoAEliminar) {
                temporal << linea << "\n";
            }
        }
        archivo.close();
        temporal.close();
        remove("reservas.txt");
        rename("reserva_temp.txt", "reservas.txt");
        cout << "\nReserva elimina exitosamente";
    }else{
        cout << "\nEliminacion cancelada";
    }
}
