#include <iostream>

#include "../include/memory/Proceso.h"
#include "../include/memory/MemoriaRAM.h"

int main() {
    MemoriaRAM memoria = MemoriaRAM(1024);

    memoria.imprimirMapaMemoria();

    Proceso proceso1 = Proceso(1, "Musica", 100);
    Proceso proceso2 = Proceso(2, "Uma Musume", 500);

    return 0;
}