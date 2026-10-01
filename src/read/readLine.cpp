#include <read/readLine.hpp>
#include <error/applicationError.hpp>

constexpr std::size_t MAX_LINE_BYTES = 256;
constexpr size_t DELIMITER_SIZE{1};
using lineBuffer = std::array<char, MAX_LINE_BYTES + DELIMITER_SIZE>;

size_t compute_length_of_line(std::streamsize gcount, bool eof) {
    if (eof) {
        return static_cast<size_t>(gcount);
    }

    return static_cast<size_t>(gcount - DELIMITER_SIZE);
}

[[nodiscard]]
bool read_line(std::istream& input, std::string& line, std::size_t line_number) {
    lineBuffer buffer{};
    line.clear();
    
    input.getline(buffer.data(), buffer.size());

    if (input.bad()) {
        throw ApplicationError{exitCode::INPUT_ERROR,
            "Chyba pri cteni radku " + std::to_string(line_number)};
    }

    bool isBufferEmpty = input.gcount() == 0;
    bool isEndOfFile = input.eof();
    if (isEndOfFile && isBufferEmpty) return false;

    if (input.fail()) {
        throw ApplicationError{exitCode::INPUT_ERROR, 
            "Radek " + std::to_string(line_number) 
                + ": Maximalni delka je " 
                + std::to_string(MAX_LINE_BYTES) 
                + " bajtu"
        };
    }

    const size_t length = compute_length_of_line(input.gcount(), isEndOfFile);
    line.assign(buffer.data(), length);

    return true;
}