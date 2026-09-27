#include <validation/schema/tokens/rectangleTokensSchema.hpp>
#include <util/parse/Number.hpp>

#include <cmath>
#include <cstddef>


constexpr std::size_t EXPECTED_TOKEN_COUNT = 5;
constexpr std::size_t X_INDEX = 1;
constexpr std::size_t Y_INDEX = 2;
constexpr std::size_t WIDTH_INDEX = 3;
constexpr std::size_t HEIGHT_INDEX = 4;

const Schema<Tokens> rectangleTokensSchema{
    {
        "arguments",
        "Ocekavany format: rect <x> <y> <w> <h>",
        [](const Tokens& tokens) {
            return tokens.size() == EXPECTED_TOKEN_COUNT
                && tokens.front() == "rect";
        }
    },
    {
        "position",
        "x a y musi byt cela cisla v rozsahu int",
        [](const Tokens& tokens) {
            return parse_number<int>(tokens[X_INDEX]).has_value()
                && parse_number<int>(tokens[Y_INDEX]).has_value();
        }
    },
    {
        "width",
        "Sirka musi byt konecne cislo vetsi nez nula",
        [](const Tokens& tokens) {
            const auto width = parse_number<double>(tokens[WIDTH_INDEX]);
            return width.has_value() && std::isfinite(width.value())
                && width.value() > 0.0;
        }
    },
    {
        "height",
        "Vyska musi byt konecne cislo vetsi nez nula",
        [](const Tokens& tokens) {
            const auto height = parse_number<double>(tokens[HEIGHT_INDEX]);
            return height.has_value() && std::isfinite(height.value())
                && height.value() > 0.0;
        }
    }
};
