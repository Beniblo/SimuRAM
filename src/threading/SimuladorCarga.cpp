#include "../../include/threading\SimuladorCarga.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>

// Constructor de clase
SimuladorCarga::SimuladorCarga(MemoriaRAM& ram) : ram(ram) {

};

// Destructor
SimuladorCarga::~SimuladorCarga() {}

// Metodo para agregar procesos
void SimuladorCarga::tareaProceso(int id,
                                  std::string nombre,
                                  int tamanio,
                                  int tiempoUso)
{
    // Instancio el proceso nuevo
    std::unique_ptr<Proceso> proceso = std::make_unique<Proceso>
    (
      id,
      nombre,
      tamanio
    );

    // Genero variable de bool para corroborar que se si genere el proceso nuevo
    bool asigando = ram.asignarProceso(std::move(proceso));

    // Comparativa para corroborar que se si genere el proceso nuevo
    if (asigando) {
        // Dormir durante el tiempo de uso asignado
        std::this_thread::sleep_for(std::chrono::seconds(tiempoUso));
        // Liberar espacio al terminar el tiempo del proceso
        ram.liberarProceso(id);
    }else {
        std::cout << "[Error] no hay RAM disponible para la carga " << nombre << "\n";
        // Cuando pasa el tiempo se debe liberar el espacio
    }
};

// Funcion para Simular los hilos
void SimuladorCarga::iniciarSimuladorCargaConcurrente() {
    // Genero un vector de Hilos para la simulacion
    std::vector<std::thread> hilos;

    // Inserto 4 hilos
    hilos.emplace_back
    (
        &SimuladorCarga::tareaProceso,
        this,
        10,
        "Opera GX",
        200, // Tamaño en Memoria
        3
    );

    hilos.emplace_back
    (
        &SimuladorCarga::tareaProceso,
        this,
        20,
        "UmaMusume",
        600,
        5
    );

    hilos.emplace_back
    (
        &SimuladorCarga::tareaProceso,
        this,
        30,
        "Windows Defender",
        100,
        2
    );

    hilos.emplace_back
    (
        &SimuladorCarga::tareaProceso,
        this,
        40,
        "Discord",
        150,
        4
    );

    // Necesario para que cada hilo termine
    for (std::thread& hilo : hilos) {
        hilo.join();
    }
};