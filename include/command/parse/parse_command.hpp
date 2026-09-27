#ifndef PARSE_COMMAND_HPP
#define PARSE_COMMAND_HPP

#include <vector>
#include <functional>
#include <filesystem>
#include <memory>
#include <string_view>
#include <command/ICommand.hpp>

using Tokens = std::vector<std::string_view>;
using CommandFactory = std::function<std::unique_ptr<ICommand>(const Tokens&)>;

std::unique_ptr<ICommand> parse_command(std::string_view line, size_t line_number);

#endif
