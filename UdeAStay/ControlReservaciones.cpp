#include "usuario.h"
#include "alojamiento.h"
#include "reservacion.h"
#include <cstring>
#include <cstdio>
#include <iostream>

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

void sumarDias(const char* fecha, int dias, int& dia, int& mes, int& año){
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
}

const char* nombreDia(int dia, int mes, int año){

}
