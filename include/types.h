#ifndef EMUFRONT_TYPES_H_
#define EMUFRONT_TYPES_H_

#include <sched.h>
#include <string>
#include <vector>

namespace emufront {


struct SystemProfile {
    struct Executable {
        std::string path;
        std::string args;

        pid_t run(const std::string& rom_path) const;
    };

    std::string sys_name;
    std::string display_name;
    std::string rom_dir;
    std::vector<std::string> valid_rom_extensions;
    Executable emulator;
};


} // namespace emufront

#endif
