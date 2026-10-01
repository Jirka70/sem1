#include "exitCode.hpp"
#include "application.hpp"

#include <iostream>
#include <error/applicationError.hpp>

void print_result(const ApplicationResult& result) {
    if (result.status == applicationStatus::OK) {
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