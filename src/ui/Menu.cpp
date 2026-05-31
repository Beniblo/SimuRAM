#include "../../include/ui/Menu.h"

#include <iostream>

Menu::Menu(MemoriaRAM& ram, SimuladorCarga& simulador)
    : ram(ram),
    simulador(simulador)
{

}

Menu::~Menu() {}

// Metodo que se encarga de mostrar el menu xd
void Menu::mostrarMenu() {
    int opcion;

    while (true) {
        std::cout << "=====SimuRAM====\n";
        std::cout << "1. Mostrar Estado RAM\n";
        std::cout << "2. Iniciar Simulacion\n";
        std::cout << "3. Salir\n";
        std::cout << "Selecciona una opcion: ";

        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ram.imprimirMapaMemoria();
                break;

            case 2:
                simulador.iniciarSimuladorCargaConcurrente();
                break;

            case 3:
                std::cout << "Saliendo de SimuRAM\n";
                return;

            default:
                std::cout << "Opcion no valida\n";
                break;
        }
    }
}