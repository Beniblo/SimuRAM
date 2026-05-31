#include "../../include/persistence/Logger.h"
#include <string>
#include <fstream>
#include <iostream>
#include <mutex>

// Instancio mi archivo logger
std::mutex Logger::mtx_archivo;

// Funcion para realizar el registro de operacion
void Logger::registrarOperacion(const std::string &mensaje) {
    std::lock_guard<std::mutex> lock(mtx_archivo);

    // Defino la ruta donde se creara o modificara el archivo del logger txt
    std::ofstream archivo("../data/logs/registro_ram.txt", std::ios::app);

    // Condicional para confirmar que el archivo se haya abierto
    if (archivo.is_open()) {
        archivo << mensaje << "\n";
    }else {
        std::cout << "Error al abrir el archivo" << "\n";
    }
}
