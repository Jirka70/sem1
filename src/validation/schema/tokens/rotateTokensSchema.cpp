#include <validation/schema/tokens/rotateTokensSchema.hpp>
#include <util/parse/Number.hpp>

#include <cmath>
#include <cstddef>

constexpr std::size_t EXPECTED_TOKEN_COUNT = 4;
constexpr std::size_t X_INDEX = 1;
constexpr std::size_t Y_INDEX = 2;
constexpr std::size_t ANGLE_INDEX = 3;

const Schema<Tokens> rotateTokensSchema{
    {
        "arguments",
        "Ocekavany format: rotate <x> <y> <a>",
        [](const Tokens& tokens) {
            return tokens.size() == EXPECTED_TOKEN_COUNT
                && tokens.front() == "rotate";
        }
    },
    {
        "center",
        "Souradnice stredu musi byt cela cisla v rozsahu int",
        [](const Tokens& tokens) {
            return parse_number<int>(tokens[X_INDEX]).has_value()
                && parse_number<int>(tokens[Y_INDEX]).has_value();
        }
    },
    {
        "angle",
        "Uhel musi byt konecne realne cislo",
        [](const Tokens& tokens) {
            const auto angle =
                parse_number<double>(tokens[ANGLE_INDEX]);

            return angle.has_value()
                && std::isfinite(*angle);
        }
    }
};