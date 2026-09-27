#include <validation/schema/shape/lineSchema.hpp>
#include <cmath>

const Schema<Line> lineSchema{
    {
        "start",
        "Souradnice pocatecniho bodu musi byt konecna cisla",
        [](const Line& args) {
            return std::isfinite(args.start.x)
                && std::isfinite(args.start.y);
        }
    },
    {
        "end",
        "Souradnice koncoveho bodu musi byt konecna cisla",
        [](const Line& args) {
            return std::isfinite(args.end.x)
                && std::isfinite(args.end.y);
        }
    },
    {
        "points",
        "Pocatecni a koncovy bod nesmi byt totozne",
        [](const Line& args) {
            return args.start.x != args.end.x
                || args.start.y != args.end.y;
        }
    }
};