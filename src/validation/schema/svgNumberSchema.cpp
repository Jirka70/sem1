#include <validation/schema/svgNumberSchema.hpp>

#include <cmath>

const schema<double> svgNumberSchema{
    {
        "svg_number",
        "SVG hodnota musi byt konecne cislo",
        [](const double& value) {
            return std::isfinite(value);
        }
    }
};