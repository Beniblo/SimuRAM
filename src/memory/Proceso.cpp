#include "../../include/memory/Proceso.h"

#include <iostream>
#include <string>

// Hago el constructor del Proceso
Proceso::Proceso(int idProcesp,
                 std::string nombreProceso,
                 int tamanioProceso)

    : idProceso(idProcesp),
      nombreProceso(std::move(nombreProceso)),
      tamanioProceso(tamanioProceso)
{
    std::cout << "[Proceso] "<< this->nombreProceso << " creado con exito\n" << "\n";
}

// Hago el destructor del Proceso
Proceso::~Proceso() {
    std::cout << "[Proceso] " << nombreProceso << " con ID: " << idProceso
    << " terminado y destruido\n" << "\n";
}