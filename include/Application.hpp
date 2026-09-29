#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <cstddef>
#include <string>
#include <ExitCode.hpp>

enum class ApplicationStatus {
    OK,
    FAILURE
};

struct ApplicationResult {
    ApplicationStatus status;
    ExitCode exitCode;
    std::size_t processed_lines;
    std::string error_message;
};

class Application {
public: 
    ApplicationResult run(int argc, char* argv[]);
};

#endif