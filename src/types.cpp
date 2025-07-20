#include "types.h"

#include <cstddef>
#include <sched.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "string_helper.h"


namespace emufront {


constexpr std::string ROM_PATH_REPLACE = "%ROM_PATH%";


pid_t emufront::SystemProfile::Executable::run(const std::string& rom_path) const {
    std::string full_args = this->path;

    full_args.append(" ");
    full_args.append(this->args);

    std::string quoted_rom_path = "\"";
    quoted_rom_path.append(rom_path);
    quoted_rom_path.push_back('\"');

    full_args = replace_all(full_args, ROM_PATH_REPLACE, quoted_rom_path);

    std::vector<std::string> arg_array = parse_shell_args(full_args);

    std::vector<const char*> command;
    for (size_t i = 0; i < arg_array.size(); i++) {
        command.push_back(arg_array[i].c_str());
    }
    command.push_back(NULL);

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execvp(command[0], const_cast<char* const*>(command.data()));

        perror("execvp failed");
        _exit(127);
    }
    else if (pid > 0) {
        // Parent, no errors
    }
    else if (pid < 0) {
        // Error
        perror("fork");
    }


    return pid;
}


} // namespace emufront
