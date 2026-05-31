#pragma once

#include <string>
#include <fstream>
#include <mutex>

class Logger {
private:
    static std::mutex mtx_archivo;

public:
    static void registrarOperacion(const std::string& mensaje);
};