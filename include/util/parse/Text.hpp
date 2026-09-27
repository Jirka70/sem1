#ifndef PARSING_TEXT_HPP
#define PARSING_TEXT_HPP

#include <string_view>
#include <vector>
#include <command/parse/parse_command.hpp>

std::vector<std::string_view> split(std::string_view text, std::string_view separator);
Tokens tokenize(std::string_view text);

#endif