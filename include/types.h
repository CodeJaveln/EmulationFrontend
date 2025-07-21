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

struct RomProfile {
    // Valid path to pass in system.emulator.run
    std::string rom_path;

    // Taken from system.rom_dir somewhere
    std::string rom_dir_path;
    // To default to for displaying
    std::string dir_name;

    const SystemProfile& system;

    RomProfile(const SystemProfile& sys) : system(sys) {}
};


} // namespace emufront

#endif
