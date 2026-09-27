#include <read/readLine.hpp>
#include <error/ApplicationError.hpp>

constexpr std::size_t MAX_LINE_BYTES = 256;
constexpr size_t DELIMITER_SIZE{1};
using LineBuffer = std::array<char, MAX_LINE_BYTES + DELIMITER_SIZE>;

int computeLengthOfLine(int gcount, bool eof) {
    if (eof) {
        return gcount;
    }

    return gcount - DELIMITER_SIZE;
}

[[nodiscard]]
bool readLine(std::istream& input, std::string& line, std::size_t line_number) {
    LineBuffer buffer{};
    line.clear();
    
    input.getline(buffer.data(), buffer.size());

    if (input.bad()) {
        throw ApplicationError{ExitCode::input_error,
            "Chyba pri cteni radku " + std::to_string(line_number)};
    }

    bool isBufferEmpty = input.gcount() == 0;
    bool isEndOfFile = input.eof();
    if (isEndOfFile && isBufferEmpty) return false;

    if (input.fail()) {
        throw ApplicationError{ExitCode::input_error, 
            "Radek " + std::to_string(line_number) 
                + ": Maximalni delka je " 
                + std::to_string(MAX_LINE_BYTES) 
                + " bajtu"
        };
    }

    const size_t length = computeLengthOfLine(input.gcount(), isEndOfFile);
    line.assign(buffer.data(), length);

    return true;
}