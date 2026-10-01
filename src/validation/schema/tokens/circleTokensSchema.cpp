#include <validation/schema/tokens/circleTokensSchema.hpp>
#include <util/parse/number.hpp>

#include <cmath>
#include <cstddef>

constexpr std::size_t EXPECTED_TOKEN_COUNT = 4;
constexpr std::size_t X_INDEX = 1;
constexpr std::size_t Y_INDEX = 2;
constexpr std::size_t RADIUS_INDEX = 3;

const schema<tokens> circleTokensSchema{
    {
        "arguments",
        "Ocekavany format: circle <x> <y> <radius>",
        [](const tokens& tokens) {
            return tokens.size() == EXPECTED_TOKEN_COUNT
                && tokens.front() == "circle";
        }
    },
    {
        "center",
        "Souradnice stredu musi byt konecna cisla",
        [](const tokens& tokens) {
            const auto x = parse_number_t<double>(tokens[X_INDEX]);
            const auto y = parse_number_t<double>(tokens[Y_INDEX]);
            return x.has_value() && y.has_value()
                && std::isfinite(x.value()) && std::isfinite(y.value());
        }
    },
    {
        "radius",
        "Polomer musi byt konecne cislo vetsi nez nula",
        [](const tokens& tokens) {
            const auto radius = parse_number_t<double>(tokens[RADIUS_INDEX]);
            return radius.has_value() && std::isfinite(radius.value())
                && radius.value() > 0.0;
        }
    }
};
