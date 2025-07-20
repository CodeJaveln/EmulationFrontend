#include "string_helper.h"

#include <cstddef>
#include <string>

namespace emufront {

std::string replace_all(std::string str, const std::string& from, const std::string& to) {
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }

    return str;
}

std::vector<std::string> parse_shell_args(const std::string& full_arg_str) {
    std::vector<std::string> args;

    size_t token_index = 0;
    char quote_mode = '\0';
    bool in_token = false;

    for (size_t i = 0; full_arg_str[i] != '\0'; i++) {
        if ((full_arg_str[i] == '\"' || full_arg_str[i] == '\'') && quote_mode == '\0') {
            quote_mode = full_arg_str[i];
            token_index = i + 1;
            in_token = true;

            continue;
        }
        else if (full_arg_str[i] == quote_mode) {
            quote_mode = '\0';
            in_token = false;

            args.push_back(full_arg_str.substr(token_index, i - token_index));

            continue;
        }
        else if (quote_mode != '\0') {
            // Quotes inside another type of quote is allowed

            continue;
        }

        else if (in_token && full_arg_str[i] == ' ') {
            in_token = false;

            args.push_back(full_arg_str.substr(token_index, i - token_index));
        }
        else if (!in_token && full_arg_str[i] != ' ') {
            in_token = true;
            token_index = i;
        }
    }
    
    if (in_token) {
        args.push_back(full_arg_str.substr(token_index, full_arg_str.length() - token_index));
    }

    return args;
}


} // namespace emufront
