
#include "ExitCode.hpp"
#include "Application.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    try {
        Application app;
        app.run(argc, argv);
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return static_cast<int>(ExitCode::failure);
    }
}