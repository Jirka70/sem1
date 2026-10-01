#ifndef SEM1_COMMAND_PARSE_PARSE_COMMAND_HPP
#define SEM1_COMMAND_PARSE_PARSE_COMMAND_HPP

#include <vector>
#include <functional>
#include <filesystem>
#include <memory>
#include <string_view>
#include <command/iCommand.hpp>
#include <util/parse/text.hpp>

using commandFactory = std::function<std::unique_ptr<ICommand>(const tokens&)>;

std::unique_ptr<ICommand> parse_command(const tokens& tokens, size_t line_number);

#endif
