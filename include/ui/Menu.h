#pragma once

#include "../../include/memory/MemoriaRAM.h"
#include "../../include/threading/SimuladorCarga.h"

class Menu {
private:
    MemoriaRAM& ram;
    SimuladorCarga& simulador;

public:
    Menu(MemoriaRAM& ram, SimuladorCarga& simulador);

    ~Menu();

    void mostrarMenu();
};