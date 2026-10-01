#include <validation/schema/tokens/scaleTokensSchema.hpp>
#include <util/parse/number.hpp>

#include <cmath>
#include <cstddef>

constexpr std::size_t EXPECTED_TOKEN_COUNT = 4;
constexpr std::size_t X_INDEX = 1;
constexpr std::size_t Y_INDEX = 2;
constexpr std::size_t FACTOR_INDEX = 3;

const schema<tokens> scaleTokensSchema{
    {
        "arguments",
        "Ocekavany format: scale <x> <y> <f>",
        [](const tokens& tokens) {
            return tokens.size() == EXPECTED_TOKEN_COUNT
                && tokens.front() == "scale";
        }
    },
    {
        "center",
        "Souradnice stredu musi byt cela cisla v rozsahu int",
        [](const tokens& tokens) {
            return parse_number_t<int>(tokens[X_INDEX]).has_value()
                && parse_number_t<int>(tokens[Y_INDEX]).has_value();
        }
    },
    {
        "factor",
        "Faktor musi byt konecne nenulove realne cislo",
        [](const tokens& tokens) {
            const auto factor =
                parse_number_t<double>(tokens[FACTOR_INDEX]);

            return factor.has_value()
                && std::isfinite(*factor)
                && *factor != 0.0;
        }
    }
};