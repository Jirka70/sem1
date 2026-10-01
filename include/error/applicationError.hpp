#ifndef SEM1_ERROR_APPLICATION_ERROR_HPP
#define SEM1_ERROR_APPLICATION_ERROR_HPP

#include <stdexcept>
#include <exitCode.hpp>


class applicationError : public std::runtime_error {
public:
    applicationError(exitCode code, const std::string& message) : std::runtime_error(message), code_(code) {}

    exitCode code() const noexcept {    
        return code_;
    }

private:
    exitCode code_;
};

#endif