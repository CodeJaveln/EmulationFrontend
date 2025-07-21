#include "config.h"

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>
#include "inipp/inipp.h"
#include "string_helper.h"
#include "types.h"

namespace emufront {

std::optional<std::vector<SystemProfile>> parse_systems(std::string ini_path) {
    std::vector<SystemProfile> systems;
    inipp::Ini<char> ini;
    std::ifstream is(ini_path);
    std::unordered_map<std::string, std::function<void(SystemProfile&, const std::string&)>> handler_map = {
        { "display_name", [](SystemProfile& s, const std::string& v) { s.display_name = v; } },
        { "rom_dir", [](SystemProfile& s, const std::string& v) { s.rom_dir = v; } },
        { "rom_ext", [](SystemProfile& s, const std::string& v) { std::vector<std::string> valid_ext = split(v, ','); s.valid_rom_extensions = valid_ext; } },
        { "exe_path", [](SystemProfile& s, const std::string& v) { s.emulator.path = v; } },
        { "args", [](SystemProfile& s, const std::string& v) { s.emulator.args = v; } },

    };
    std::unordered_set<std::string> processed_keys;

    ini.parse(is);

    for (const auto& [section, section_kv_map] : ini.sections) {
        processed_keys.clear();

        SystemProfile system_profile{};
        system_profile.sys_name = section;

        for (const auto& [key, value] : section_kv_map) {
            auto it = handler_map.find(key);
            if (it == handler_map.end()) {
                std::cout << "Unrecognizable key in ini file: " << key << std::endl;
                return std::nullopt;
            }

            it->second(system_profile, value);
            processed_keys.insert(key);
        }

        if (processed_keys.size() != handler_map.size()) {
            std::cout << "Insufficient keys in ini file for system" << std::endl;
            return std::nullopt;
        }

        systems.push_back(system_profile);
    }

    return systems;
}


std::vector<RomProfile> read_roms(const std::vector<SystemProfile>& systems) {
    std::vector<RomProfile> rom_profiles;

    for (size_t i = 0; i < systems.size(); i++) {
        for (const auto& entry : std::filesystem::directory_iterator(systems[i].rom_dir)) {
            if (!entry.is_directory()) {
                continue;
            }

            RomProfile rom(systems[i]);
            auto entry_dir = std::filesystem::absolute(std::filesystem::path(systems[i].rom_dir) / entry.path().filename());

            rom.rom_dir_path = entry_dir.string();
            rom.dir_name = entry.path().filename();

            if (!
            for (const auto& rom_dir_entry : std::filesystem::directory_iterator(rom.rom_dir_path)) {
                if (!rom_dir_entry.is_directory() && std::find(systems[i].valid_rom_extensions.begin(), systems[i].valid_rom_extensions.end(), rom_dir_entry.path().extension()) != systems[i].valid_rom_extensions.end()) {
                    rom.rom_path = std::filesystem::absolute(std::filesystem::path(entry_dir) / rom_dir_entry.path().filename()).string();
                    break;
                }
            }


            rom_profiles.push_back(rom);
        }
    }

    return rom_profiles;
}

}
