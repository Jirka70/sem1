#include <validation/schema/tokens/lineTokensSchema.hpp>
#include <util/parse/Number.hpp>

#include <cmath>
#include <cstddef>

namespace {
constexpr std::size_t EXPECTED_TOKEN_COUNT = 5;
constexpr std::size_t START_X_INDEX = 1;
constexpr std::size_t START_Y_INDEX = 2;
constexpr std::size_t END_X_INDEX = 3;
constexpr std::size_t END_Y_INDEX = 4;
} // namespace

const Schema<Tokens> lineTokensSchema{
    {
        "arguments",
        "Ocekavany format: line <x1> <y1> <x2> <y2>",
        [](const Tokens& tokens) {
            return tokens.size() == EXPECTED_TOKEN_COUNT
                && tokens.front() == "line";
        }
    },
    {
        "start",
        "Souradnice pocatecniho bodu musi byt konecna cisla",
        [](const Tokens& tokens) {
            const auto x = parse_number<double>(tokens[START_X_INDEX]);
            const auto y = parse_number<double>(tokens[START_Y_INDEX]);
            return x.has_value() && y.has_value()
                && std::isfinite(*x) && std::isfinite(*y);
        }
    },
    {
        "end",
        "Souradnice koncoveho bodu musi byt konecna cisla",
        [](const Tokens& tokens) {
            const auto x = parse_number<double>(tokens[END_X_INDEX]);
            const auto y = parse_number<double>(tokens[END_Y_INDEX]);
            return x.has_value() && y.has_value()
                && std::isfinite(*x) && std::isfinite(*y);
        }
    }
};
