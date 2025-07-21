#ifndef CONFIG_H_
#define CONFIG_H_

#include <optional>
#include <string>
#include <vector>
#include "types.h"

namespace emufront {

std::optional<std::vector<SystemProfile>> parse_systems(std::string ini_path);

}

#endif
