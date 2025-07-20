#include "config.h"

#include <fstream>
#include <vector>
#include "inipp/inipp.h"

namespace emufront {

std::vector<SystemProfile> parse_systems(std::string ini_path) {
    std::vector<SystemProfile> systems;
    inipp::Ini<char> ini;
    std::ifstream is(ini_path);

    return systems;
}

}
