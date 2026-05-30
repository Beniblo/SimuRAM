#pragma once

#include <vector>
#include <mutex>
#include <unordered_map>
#include <memory>
#include "../../include/memory/BloqueMemoria.h"
#include "../../include/memory/Proceso.h"

// Defino la Clase MemoriaRAM
class MemoriaRAM {
// Defino los atributos en privado
private:
    int capacidadTotal;
    std::vector<BloqueMemoria> bloques;
    std::unordered_map<int, std::unique_ptr<Proceso>> tablaProcesos;
    mutable std::mutex mtx_memoria;

public:
    // Constructor
    MemoriaRAM(int capacidadTotal);

    // Destructor
    ~MemoriaRAM();

    // Metodos
    void imprimirMapaMemoria() const;

    bool asignarProceso(std::unique_ptr<Proceso> nuevoProceso);

    bool liberarProceso(int idProceso);

    void compactarMemoria();
};
