#pragma once

#include <vector>
#include <thread>
#include <memory>
#include "../memory/MemoriaRAM.h"

class SimuladorCarga {
private:
    MemoriaRAM& ram;

    void tareaProceso(int id, std::string nombre,
                      int tamanio, int tiempoUso);

public:
    SimuladorCarga(MemoriaRAM& ram);

    ~SimuladorCarga();

    void iniciarSimuladorCargaConcurrente();
};