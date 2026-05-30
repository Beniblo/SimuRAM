#include "../include/memory/Proceso.h"
#include "../include/memory/MemoriaRAM.h"
#include "../include/threading/SimuladorCarga.h"

int main() {
    MemoriaRAM memoria = MemoriaRAM(1024);

    SimuladorCarga simulador = SimuladorCarga(memoria);

    // Impresion de memoria por default
    memoria.imprimirMapaMemoria();

    // Inciar la simulacion de multihilo
    simulador.iniciarSimuladorCargaConcurrente();

    //  Impresion de memoria
    memoria.imprimirMapaMemoria();

    return 0;
}
