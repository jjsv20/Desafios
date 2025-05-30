#include "usuario.h"
#include "alojamiento.h"
#include "reservacion.h"
#include "sesion.h"
#include "medicionmemoria.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

void reservarAlojamiento(Usuario* huesped, Alojamiento** alojamientos, int totalAlojamientos, Reservacion**& reservas, int& totalReservas);
void anularReservas(Usuario* usuario, Reservacion**& reservas, int& totalReservas);
void consultarReservacionesAnfitrion(Usuario* anfitrion, Reservacion** reservas, int totalReservas);
void gestionarEstadoReservacion(Usuario* anfitrion, Reservacion** reservas, int totalReservas);
void consultarHistorico(Usuario* anfitrion);
void generarReporteOcupacion(Usuario* anfitrion, Alojamiento** alojamientos, int totalAlojamientos, Reservacion** reservas, int totalReservas);

void gestionarEstadoReservacion(Usuario* anfitrion, Reservacion** reservas, int totalReservas) {
    cout << "\n--- Gestionar Estado de Reservaciones ---" << endl;

    // Mostrar reservaciones del anfitrión
    bool tieneReservas = false;
    cout << "Tus reservaciones:" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < totalReservas; i++) {
        // Verificar si la reserva pertenece a un alojamiento del anfitrión
        if (strcmp(reservas[i]->getAlojamiento()->getAnfitrion()->getDocumento(), anfitrion->getDocumento()) == 0) {
            tieneReservas = true;
            cout << "Código: " << reservas[i]->getCodigoReservacion()
                 << " | Alojamiento: " << reservas[i]->getAlojamiento()->getNombreAlojamiento()
                 << " | Huésped: " << reservas[i]->getDocumentoHuesped()->getNombreUsuario()
                 << " | Fecha: " << reservas[i]->getFechaEntrada()
                 << " | Duración: " << reservas[i]->getDuracion() << " noches"
                 << " | Estado: " << reservas[i]->getEstado()
                 << " | Monto: $" << reservas[i]->getMonto() << endl;
        }
    }

    if (!tieneReservas) {
        cout << "No tienes reservaciones." << endl;
        return;
    }

    char codigoReserva[20];
    cout << "\nIngrese código de la reservación a gestionar: ";
    cin >> codigoReserva;

    // Buscar la reservación
    Reservacion* reservaEncontrada = nullptr;
    for (int i = 0; i < totalReservas; i++) {
        if (strcmp(reservas[i]->getCodigoReservacion(), codigoReserva) == 0 &&
            strcmp(reservas[i]->getAlojamiento()->getAnfitrion()->getDocumento(), anfitrion->getDocumento()) == 0) {
            reservaEncontrada = reservas[i];
            break;
        }
    }

    if (!reservaEncontrada) {
        cout << "Reservación no encontrada o no es tuya." << endl;
        return;
    }

    cout << "\nReservación encontrada:" << endl;
    cout << "Estado actual: " << reservaEncontrada->getEstado() << endl;
    cout << "Huésped: " << reservaEncontrada->getDocumentoHuesped()->getNombreUsuario() << endl;
    cout << "Alojamiento: " << reservaEncontrada->getAlojamiento()->getNombreAlojamiento() << endl;

    cout << "\nOpciones:" << endl;
    cout << "1. Aprobar reservación" << endl;
    cout << "2. Rechazar reservación" << endl;
    cout << "3. Cancelar" << endl;
    cout << "Seleccione una opción: ";

    int opcion;
    cin >> opcion;

    switch (opcion) {
    case 1:
        reservaEncontrada->setEstado("Aprobada");
        cout << "Reservación aprobada exitosamente." << endl;
        break;
    case 2:
        reservaEncontrada->setEstado("Rechazada");
        cout << "Reservación rechazada." << endl;
        break;
    case 3:
        cout << "Operación cancelada." << endl;
        break;
    default:
        cout << "Opción inválida." << endl;
    }
}

void consultarHistorico(Usuario* anfitrion) {
    cout << "\n--- Consultar Histórico ---" << endl;
    cout << "Anfitrión: " << anfitrion->getNombreUsuario() << endl;
    cout << "----------------------------------------" << endl;

    ifstream archivo("historico.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo histórico o no existe." << endl;
        cout << "El archivo histórico se crea automáticamente cuando hay reservaciones completadas." << endl;
        return;
    }

    string linea;
    bool encontroHistorico = false;
    int contador = 0;

    while (getline(archivo, linea)) {
        // Saltar líneas vacías o comentarios
        if (linea.empty() || linea[0] == '#') continue;

        contador++;
        cout << "Registro " << contador << ": " << linea << endl;
        encontroHistorico = true;
    }

    if (!encontroHistorico) {
        cout << "El archivo histórico está vacío." << endl;
        cout << "No hay reservaciones completadas registradas." << endl;
    } else {
        cout << "\nTotal de registros históricos: " << contador << endl;
    }

    archivo.close();
}

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
                        //mostrarConsumoDeRecursos();
                        break;
                    case 2:
                        anularReservas(usuario, reservas, totalReservas);
                        //mostrarConsumoDeRecursos();
                        break;
                    case 3:
                        cout << "Cerrando sesión...\n";
                        break;
                    default:
                        cout << "Opción inválida.\n";
                    }
                } while (opcionHuesped != 3);

            } else if (usuario->getRol() == 'A') {
                int opcionAnfitrion = 0;
                do {
                    cout << "\n--- Menú Anfitrión ---" << endl;
                    cout << "1. Consultar reservaciones pendientes" << endl;
                    cout << "2. Gestionar estado de reservaciones" << endl;
                    cout << "3. Consultar histórico" << endl;
                    cout << "4. Reporte de ocupación" << endl;
                    cout << "5. Cerrar sesión" << endl;
                    cout << "Seleccione una opción: ";
                    cin >> opcionAnfitrion;

                    switch (opcionAnfitrion) {
                    case 1:
                        consultarReservacionesAnfitrion(usuario, reservas, totalReservas);
                        mostrarConsumoDeRecursos();
                        break;
                    case 2:
                        gestionarEstadoReservacion(usuario, reservas, totalReservas);
                        mostrarConsumoDeRecursos();
                        break;
                    case 3:
                        consultarHistorico(usuario);
                        mostrarConsumoDeRecursos();
                        break;
                    case 4:
                        generarReporteOcupacion(usuario, alojamientos, totalAlojamientos, reservas, totalReservas);
                        mostrarConsumoDeRecursos();
                        break;
                    case 5:
                        cout << "Cerrando sesión...\n";
                        sesion.cerrarSesion();
                        break;
                    default:
                        cout << "Opción inválida.\n";
                    }
                } while (opcionAnfitrion != 5);
            }

        } else if(opcionPrincipal == 2){
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

    mostrarConsumoDeRecursos();
    return 0;
}
