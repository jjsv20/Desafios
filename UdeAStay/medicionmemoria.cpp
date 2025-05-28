#include "medicionmemoria.h"
#include <windows.h>
#include <psapi.h>
#include <iostream>


using namespace std;

int iteraciones = 0;

void mostrarConsumoDeRecursos(){
    PROCESS_MEMORY_COUNTERS pmc;
    SIZE_T memoriaUtilizada = 0;
    if(GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))){
        memoriaUtilizada = pmc.WorkingSetSize;
    }
    cout << "\n ---- Medicion de Recursos ----\n";
    cout << "Iteraciones realizadas: " << iteraciones << endl;
    cout << "Memoria utilizada: " << (memoriaUtilizada / 1024) << " KB (" << (memoriaUtilizada / (1024 * 1024)) << " MB)" << endl;
}
