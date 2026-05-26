#include "../../include/memory/BloqueMemoria.h"

#include <iostream>

BloqueMemoria::BloqueMemoria(int direccionInicio,
                             int tamanio,
                             EstadoBloque estado,
                             int idProcesoAsignado)

    : direccionInicio(direccionInicio),
      tamanio(tamanio),
      estado(estado),
      idProcesoAsignado(idProcesoAsignado) {}

BloqueMemoria::~BloqueMemoria(){}

void BloqueMemoria::mostrarInformacion() const{

    std::string estadoTexto = (estado == EstadoBloque::LIBRE) ? "Libre" : "OCUPADO";

    std::cout << "[Dir: " << direccionInicio << " | Tam: " << tamanio
    << " MB | Estado: " << estadoTexto << " | PID: " << idProcesoAsignado << "]\n"; // PID, id del proceso (Process ID)
}