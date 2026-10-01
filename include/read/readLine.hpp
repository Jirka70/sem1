#ifndef SEM1_READ_READ_LINE_HPP
#define SEM1_READ_READ_LINE_HPP

#include <array>
#include <string>
#include <fstream>

[[nodiscard]]
bool read_line(std::istream& input, std::string& line, std::size_t line_number);

#endif

