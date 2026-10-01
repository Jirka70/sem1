#ifndef SEM1_UTIL_PARSE_TEXT_HPP
#define SEM1_UTIL_PARSE_TEXT_HPP

#include <string_view>
#include <vector>

using tokens = std::vector<std::string_view>;

std::vector<std::string_view> split(std::string_view text, std::string_view separator);
tokens tokenize(std::string_view text);

#endif