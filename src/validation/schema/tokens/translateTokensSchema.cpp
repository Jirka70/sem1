#include <validation/schema/tokens/translateTokensSchema.hpp>
#include <util/parse/number.hpp>

#include <cstddef>

constexpr std::size_t EXPECTED_TOKEN_COUNT = 3;
constexpr std::size_t X_INDEX = 1;
constexpr std::size_t Y_INDEX = 2;

const schema<tokens> translateTokensSchema{
    {
        "arguments",
        "Ocekavany format: translate <x> <y>",
        [](const tokens& tokens) {
            return tokens.size() == EXPECTED_TOKEN_COUNT
                && tokens.front() == "translate";
        }
    },
    {
        "offset",
        "Posun x a y musi byt cela cisla v rozsahu int",
        [](const tokens& tokens) {
            return parse_number_t<int>(tokens[X_INDEX]).has_value()
                && parse_number_t<int>(tokens[Y_INDEX]).has_value();
        }
    }
};