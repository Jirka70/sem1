#include <validation/schema/tokens/translateTokensSchema.hpp>
#include <util/parse/Number.hpp>

#include <cstddef>

constexpr std::size_t EXPECTED_TOKEN_COUNT = 3;
constexpr std::size_t X_INDEX = 1;
constexpr std::size_t Y_INDEX = 2;

const Schema<Tokens> translateTokensSchema{
    {
        "arguments",
        "Ocekavany format: translate <x> <y>",
        [](const Tokens& tokens) {
            return tokens.size() == EXPECTED_TOKEN_COUNT
                && tokens.front() == "translate";
        }
    },
    {
        "offset",
        "Posun x a y musi byt cela cisla v rozsahu int",
        [](const Tokens& tokens) {
            return parse_number<int>(tokens[X_INDEX]).has_value()
                && parse_number<int>(tokens[Y_INDEX]).has_value();
        }
    }
};