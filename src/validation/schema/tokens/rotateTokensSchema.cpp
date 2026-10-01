#include <validation/schema/tokens/rotateTokensSchema.hpp>
#include <util/parse/number.hpp>

#include <cmath>
#include <cstddef>

constexpr std::size_t EXPECTED_TOKEN_COUNT = 4;
constexpr std::size_t X_INDEX = 1;
constexpr std::size_t Y_INDEX = 2;
constexpr std::size_t ANGLE_INDEX = 3;

const schema<tokens> rotateTokensSchema{
    {
        "arguments",
        "Ocekavany format: rotate <x> <y> <a>",
        [](const tokens& tokens) {
            return tokens.size() == EXPECTED_TOKEN_COUNT
                && tokens.front() == "rotate";
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
        "angle",
        "Uhel musi byt konecne realne cislo",
        [](const tokens& tokens) {
            const auto angle =
                parse_number_t<double>(tokens[ANGLE_INDEX]);

            return angle.has_value()
                && std::isfinite(*angle);
        }
    }
};