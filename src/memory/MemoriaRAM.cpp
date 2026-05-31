#include "../../include/memory/MemoriaRAM.h"
#include "../../include/persistence/Logger.h"

#include <iostream>

MemoriaRAM::MemoriaRAM(int capacidadTotal) : capacidadTotal(capacidadTotal)
{
    bloques.push_back(BloqueMemoria(
                                      0,
                                      capacidadTotal,
                                      EstadoBloque::LIBRE,
                                      -1));
}

MemoriaRAM::~MemoriaRAM(){}

// Metodos
// 1. Imprimir pantalla
void MemoriaRAM::imprimirMapaMemoria() const {
    std::lock_guard<std::mutex> lock(mtx_memoria); // Candado para forzar la espera hasta liberacion

    for (const BloqueMemoria& bloqueMemoria : bloques) {
        bloqueMemoria.mostrarInformacion();
    }
}

// 2. Asignar Procesos a la RAM
bool MemoriaRAM::asignarProceso(std::unique_ptr<Proceso> nuevoProceso) {
    std::lock_guard<std::mutex> lock(mtx_memoria);
    // Defino el tamaño para comparar lo que necesito
    int tamanioRequerido = nuevoProceso->tamanioProceso;

    // Recorrido en todo el bloque de memoria
    for (size_t i = 0; i < bloques.size(); i++) {

        // Genero un bloque generico
        BloqueMemoria& bloqueActual = bloques[i];
        // Hago una comparativa para ver si el bloque esta disponible
        // Y cumple con el tamaño requerido
        if (bloqueActual.estado == EstadoBloque::LIBRE
            && bloqueActual.tamanio >= tamanioRequerido)
        {
            // Si lo esta genero una variable temporal para guardar el tamaño
            int tamanioOriginal = bloqueActual.tamanio;

            // Hago una comparativa para ver si mi variable temporal es igual a mi requerido temporal
            if (tamanioOriginal == tamanioRequerido)
            {
                // Si se cumple de manera exacta en tamaño se cambia el estado del bloque
                // Y se cambia el id actual por el id asignado
                bloqueActual.estado = EstadoBloque::OCUPADO;
                bloqueActual.idProcesoAsignado = nuevoProceso->idProceso;
            }else
            {
                // Si se cumple pero no es el tamaño exacto se debe fragmentar
                // Se crea una variable con el sobrante del original menos el requerido para guardarlo
                int espacioSobrante = tamanioOriginal - tamanioRequerido;

                // Ademas de crear una nueva direccion con el inicio(0) mas el requerido
                int nuevaDireccion = bloqueActual.direccionInicio + tamanioRequerido;

                // Se crea un nuevo bloque de memoria sobrante
                BloqueMemoria bloqueLibreSobrante(
                    nuevaDireccion,
                    espacioSobrante,
                    EstadoBloque::LIBRE,
                    -1
                );

                // El actual se cambia por el ocupado se cambia por el ocupado del requerido
                // Y se le asigna el nuevo ID de proceso
                bloqueActual.estado = EstadoBloque::OCUPADO;
                bloqueActual.tamanio = tamanioRequerido;
                bloqueActual.idProcesoAsignado = nuevoProceso->idProceso;

                // Se inserta el nuevo bloque por posicion de inicio + mas el de el indice actual mas 1
                bloques.insert(
                    bloques.begin() + i +1,
                    bloqueLibreSobrante
                );
            }

            // Se crea el nuevo proceso y se mete al mapa de tablaProceso.
            Logger::registrarOperacion("Proceso " + nuevoProceso->nombreProceso + " asignado con exito\n");
            tablaProcesos[nuevoProceso->idProceso] =
                std::move(nuevoProceso);

            // Si se cumple se manda true
            std::cout << "Bloque creado con exito\n";
            return true;
        }
    }

    // Si no se cumple la condicion inicial se manda false
    std::cout << "No se pudo crear bloque falta de espacio\n";
    return false;
}

// 3. Liberar Bloques
bool MemoriaRAM::liberarProceso(int idProceso) {
    std::lock_guard<std::mutex> lock(mtx_memoria);
    // Condicional para buscar en el mapa tablaProcesos el id solicitado
    if (tablaProcesos.find(idProceso) != tablaProcesos.end()){
        // Si encuentra el id hace un recorrido para llegar al proceso indicado
        for (size_t i = 0; i < bloques.size(); i++) {
            // Condicionbal para encontrar el id indicado
            if (bloques[i].idProcesoAsignado == idProceso) {
                // Si lo encuentra cambia el estatus de bloque a LIBRE, le asigna un id a -1 (Default)
                // Y borra el proceso de la tablaProcesos
                bloques[i].estado = EstadoBloque::LIBRE;
                bloques[i].idProcesoAsignado = -1;
                tablaProcesos.erase(idProceso);
                std::cout << "Bloque liberado con exito\n";
                Logger::registrarOperacion("Proceso liberado con exito\n");
                break;
            }
        }
        // Si se cumple manda true
        compactarMemoria();
        return true;
    }


    std::cout << "No se pudo encontrar el proceso\n";
    return false;
}

// 4. Compactar Memoria
void MemoriaRAM::compactarMemoria() {
    // Realizo un recorrido de todo el bloque de memoria
    for (int i = 0; i < (bloques.size() - 1); i++) {
        // Condicionales para confirmar que el bloque actual y el siguiente esten libres
        if (bloques[i].estado == EstadoBloque::LIBRE
            && bloques[i + 1].estado == EstadoBloque::LIBRE)
        {
            // Si se cumple se actualiza el cambio del bloque actual sumando ambos bloques
            bloques[i].tamanio = bloques[i].tamanio + bloques[i + 1].tamanio;
            // Se elimina el segundo bloque para evitar memoria duplicada
            bloques.erase(bloques.begin() + i + 1);
            // Importante retroceder el indice para evitar convinaciones posibles
            i--;
            Logger::registrarOperacion("Memoria compactado exitosamente\n");
        }
    }
}