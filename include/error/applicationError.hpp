#ifndef APPLICATION_ERROR_HPP
#define APPLICATION_ERROR_HPP

#include <stdexcept>
#include <ExitCode.hpp>


class ApplicationError : public std::runtime_error {
public:
    ApplicationError(ExitCode code, const std::string& message) : std::runtime_error(message), code_(code) {}

    ExitCode code() const noexcept {    
        return code_;
    }

private:
    ExitCode code_;
};

#endif