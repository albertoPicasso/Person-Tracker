#ifndef UTILS_H
#define UTILS_H

#include "json.hpp"// json.hpp from Niels Lohmann (https://github.com/nlohmann/json)
                     // add to readme when exists
#include <string>

using json = nlohmann::json;

class Utils {
public:
    static json readConfig(const std::string& filePath);
};

#endif 
