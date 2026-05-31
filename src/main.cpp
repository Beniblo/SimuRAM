#include "../include/memory/MemoriaRAM.h"
#include "../include/threading/SimuladorCarga.h"
#include "../include/ui/Menu.h"

int main() {
    MemoriaRAM memoria = MemoriaRAM(1024);

    SimuladorCarga simulador = SimuladorCarga(memoria);

    Menu menu = Menu(memoria, simulador);

    menu.mostrarMenu();

    return 0;
}