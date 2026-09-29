#include "ExitCode.hpp"
#include "Application.hpp"

#include <iostream>
#include <error/ApplicationError.hpp>

void print_result(const ApplicationResult& result) {
    if (result.status == ApplicationStatus::OK) {
        std::cout << result.processed_lines 
            << std::endl 
            << "OK" 
            << std::endl;
    } else {
        std::cerr << result.error_message 
            << std::endl;
    }
}

int main(int argc, char* argv[]) {
    Application app;
    const auto result = app.run(argc, argv);

    print_result(result);
    return static_cast<int>(result.exitCode);
}