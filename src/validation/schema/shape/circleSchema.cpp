
#include <cmath>
#include <shape/Shape.hpp>
#include <validation/Validation.hpp>
#include <validation/schema/shape/circleSchema.hpp>

const Schema<Circle> circleSchema {
    {
        "radius",
        "Polomer musi byt konecne cislo",
        [](const Circle& args) {
            return std::isfinite(args.radius);
        }
    },
    {
        "center",
        "Souradnice stredu musi byt konecna realna cisla",
        [](const Circle& args) {
            return std::isfinite(args.center.x) 
                && std::isfinite(args.center.y);
        }
    },
    {
        "radius",
        "Polomer musi byt vetsi nez nula",
        [](const Circle& args) {
            return args.radius > 0.0;
        }
    }
};