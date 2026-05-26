#include "../../include/memory/MemoriaRAM.h"

MemoriaRAM::MemoriaRAM(int capacidadTotal) : capacidadTotal(capacidadTotal)
{
    bloques.push_back(BloqueMemoria(
                                      0,
                                      capacidadTotal,
                                      EstadoBloque::LIBRE,
                                      -1));
}

MemoriaRAM::~MemoriaRAM(){}

void MemoriaRAM::imprimirMapaMemoria() const {
    for (const BloqueMemoria& bloqueMemoria : bloques) {
        bloqueMemoria.mostrarInformacion();
    }
}