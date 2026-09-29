#include <validation/schema/svgNumberSchema.hpp>

#include <cmath>

const Schema<double> svgNumberSchema{
    {
        "svg_number",
        "SVG hodnota musi byt konecne cislo",
        [](const double& value) {
            return std::isfinite(value);
        }
    }
};