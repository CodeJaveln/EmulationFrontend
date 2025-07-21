#ifndef EMUFRONT_STRING_HELPER_H_
#define EMUFRONT_STRING_HELPER_H_

#include <string>
#include <vector>

namespace emufront {


std::string replace_all(std::string str, const std::string& from, const std::string& to);

std::vector<std::string> split(const std::string& s, char delim);

std::vector<std::string> parse_shell_args(const std::string& full_arg_str);


} // namespace emufront

#endif
