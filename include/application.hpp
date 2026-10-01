#ifndef SEM1_APPLICATION_HPP
#define SEM1_APPLICATION_HPP

#include <cstddef>
#include <string>
#include <exitCode.hpp>

enum class applicationStatus {
    OK,
    FAILURE
};

struct applicationResult {
    applicationStatus status;
    ::exitCode exitCode;
    std::size_t processed_lines;
    std::string error_message;
};

class application {
public: 
    applicationResult run(int argc, char* argv[]);
};

#endif
