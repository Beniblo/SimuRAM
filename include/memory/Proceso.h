#pragma once

#include <string>

// Enum para marcar el estado del Bloque
enum class EstadoBloque {
    LIBRE,
    OCUPADO
};

// Defino mi clase de Proceso, que simula procesos
class Proceso {
public:
    // Atributos
    int idProceso;
    std::string nombreProceso;
    int tamanioProceso;

    // Constructor
    Proceso(int idProceso,
        std::string nombreProceso,
        int tamanioProceso);

    // Destructor
    ~Proceso();
};