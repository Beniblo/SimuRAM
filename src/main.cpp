#include "../include/memory/Proceso.h"
#include "../include/memory/MemoriaRAM.h"

int main() {
    MemoriaRAM memoria = MemoriaRAM(1024);

    auto proceso1 = std::make_unique<Proceso>(1, "Google Chrome", 300);
    auto proceso2 = std::make_unique<Proceso>(2, "Spotify", 150);

    memoria.asignarProceso(std::move(proceso1));
    memoria.asignarProceso(std::move(proceso2));

    memoria.imprimirMapaMemoria();

    memoria.liberarProceso(1);

    memoria.imprimirMapaMemoria();

    memoria.liberarProceso(2);

    memoria.imprimirMapaMemoria();

    return 0;
}