#ifndef READLINE_HPP
#define READLINE_HPP

#include <array>
#include <string>
#include <fstream>

[[nodiscard]]
bool readLine(std::istream& input, std::string& line, std::size_t line_number);

#endif

