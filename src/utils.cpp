#include "utils.h"
#include <fstream>
#include <iostream>

json Utils::readConfig(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de configuración: " << filePath << std::endl;
        return json();
    }

    json config;
    file >> config;
    return config;
}
