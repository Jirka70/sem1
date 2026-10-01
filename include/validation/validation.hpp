#ifndef SEM1_VALIDATION_VALIDATION_HPP
#define SEM1_VALIDATION_VALIDATION_HPP

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

template<typename valueType>
struct Rule {
    std::string field;
    std::string message;
    std::function<bool(const valueType&)> checkFunction;
};

template<typename valueType>
using schema = std::vector<Rule<valueType>>;

template<typename valueType>
[[nodiscard]]
std::optional<ValidationError> validate_t(const schema<valueType>& schema, const valueType& value) {
    for (const Rule<valueType>& rule : schema) {
        if (!rule.checkFunction(value)) {
            return ValidationError{
                rule.field, 
                rule.message
            };
        }
    }

    return std::nullopt;
}

template<typename valueType>
void require_validation_t(const schema<valueType>& schema, const valueType& value) {
    const auto maybeError = validate_t(schema, value);

    if (maybeError.has_value()) {
        const auto& error = maybeError.value();
        
        throw std::invalid_argument{
            error.field + ": " + error.message
        };
    }
}

#endif
