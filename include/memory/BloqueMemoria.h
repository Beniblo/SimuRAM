#pragma once

#include "../../include/memory/Proceso.h"

// Defino mi clase Bloque de Memoria
class BloqueMemoria {
public:
    // Atributos
    int direccionInicio;
    int tamanio;
    EstadoBloque estado;
    int idProcesoAsignado;

    // Constructor
    BloqueMemoria(int direccionIncio,
                  int tamanio,
                  EstadoBloque estado = EstadoBloque::LIBRE,
                  int idProcesoAsignado = -1);

    // Destructor
    ~BloqueMemoria();

    // Metodo para mostrar información
    void mostrarInformacion() const;
};

