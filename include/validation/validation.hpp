#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include <iostream>
#include <optional>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

struct ValidationError {
    std::string field;
    std::string message;
};

template<typename T>
struct Rule {
    std::string field;
    std::string message;
    std::function<bool(const T&)> checkFunction;
};

template<typename T>
using Schema = std::vector<Rule<T>>;

template<typename T>
[[nodiscard]]
std::optional<ValidationError> validate(const Schema<T>& schema, const T& value) {
    for (const Rule<T>& rule : schema) {
        if (!rule.checkFunction(value)) {
            return ValidationError{
                rule.field, 
                rule.message
            };
        }
    }

    return std::nullopt;
}

template<typename T>
void require_validation(const Schema<T>& schema, const T& value) {
    const auto maybeError = validate(schema, value);

    if (maybeError.has_value()) {
        const auto& error = maybeError.value();
        
        throw std::invalid_argument{
            error.field + ": " + error.message
        };
    }
}

#endif
