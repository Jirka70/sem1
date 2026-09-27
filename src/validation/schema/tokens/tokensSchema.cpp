#include <validation/schema/tokens/tokensSchema.hpp>

#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <util/parse/Number.hpp>
#include <span>

static const std::unordered_map<std::string_view, std::size_t> parameterCounts{
    {"circle", 3},
    {"line", 4},
    {"rotate", 3},
    {"translate", 2},
    {"rect", 4},
    {"scale", 3}
};

const Schema<Tokens> tokensSchema {
    {
        "command",
        "Chybi prikaz",
        [](const Tokens& tokens) {
            return !tokens.empty();
        }
    },
    {
        "command",
        "Neznamy prikaz",
        [](const Tokens& tokens) {
            const std::string_view command_type = tokens.front();
            return !tokens.empty() && parameterCounts.contains(command_type);
        }
    },
    {
        "parameters",
        "Nespravny pocet parametru",
        [](const Tokens& tokens) {
            if (tokens.empty()) {
                return false;
            }

            const std::string_view& command_type = tokens.front();

            if (!parameterCounts.contains(command_type)) return false;

            const auto& command = parameterCounts.find(command_type);
            const size_t expected_parameter_number = command->second;
            const size_t actual_parameter_number = tokens.size() - 1;

            return actual_parameter_number == expected_parameter_number;
        }
    },
    {
        "parameters",
        "Parametry musi byt konecna cisla",
        [](const Tokens& tokens) {
            if (tokens.empty()) {
                return false;
            }
            
            constexpr size_t PARAM_START_INDEX{1};
            const auto parameters = std::span<const std::string_view>{tokens}.subspan(PARAM_START_INDEX);

            for (const std::string_view& param : parameters) {
                const std::optional<double> number = parse_number<double>(param);

                if (!number.has_value()) return false;
                if (!std::isfinite(number.value())) return false;
            }

            return true;
        }
    }
};