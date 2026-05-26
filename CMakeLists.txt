cmake_minimum_required(VERSION 3.31)
project(SimuRAM)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimuRAM
        src/main.cpp
        src/memory/Proceso.cpp
        src/memory/BloqueMemoria.cpp
        src/memory/MemoriaRAM.cpp
)