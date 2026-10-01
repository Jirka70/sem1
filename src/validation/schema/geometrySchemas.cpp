#include <validation/schema/geometrySchemas.hpp>

#include <cmath>
#include <cstddef>



const schema<vector2D> vectorSchema{
    {
        "vector",
        "Slozky vektoru musi byt konecna cisla",
        [](const vector2D& vector) {
            return std::isfinite(vector.x)
                && std::isfinite(vector.y);
        }
    }
};

bool is_valid_vector_2d(const vector2D& vec) {
    return !validate_t(vectorSchema, vec).has_value();
}


const schema<vector2D> scaleFactorsSchema{
    {
        "scale",
        "Meritka musi byt konecna nenulova cisla",
        [](const vector2D& factors) {
            return is_valid_vector_2d(factors)
                && factors.x != 0.0
                && factors.y != 0.0;
        }
    }
};

const schema<circleArgs> circleSchema{
    {
        "center",
        "Souradnice stredu musi byt konecna cisla",
        [](const circleArgs& args) {
            return is_valid_vector_2d(args.center);
        }
    },
    {
        "radius",
        "Polomer musi byt konecne cislo vetsi nez nula",
        [](const circleArgs& args) {
            return std::isfinite(args.radius)
                && args.radius > 0.0;
        }
    }
};

const schema<lineArgs> lineSchema{
    {
        "start",
        "Pocatecni bod musi mit konecne souradnice",
        [](const lineArgs& args) {
            return is_valid_vector_2d(args.start);
        }
    },
    {
        "end",
        "Koncovy bod musi mit konecne souradnice",
        [](const lineArgs& args) {
            return is_valid_vector_2d(args.end);
        }
    },
    {
        "points",
        "Pocatecni a koncovy bod nesmi byt totozne",
        [](const lineArgs& args) {
            return args.start.x != args.end.x
                || args.start.y != args.end.y;
        }
    }
};

const schema<rectangleArgs> rectangleSchema{
    {
        "corners",
        "Vrcholy musi mit konecne souradnice",
        [](const rectangleArgs& args) {
            for (const vector2D corner : args.corners) {
                if (!is_valid_vector_2d(corner)) {
                    return false;
                }
            }

            return true;
        }
    },
    {
        "corners",
        "Vsechny vrcholy musi byt navzajem ruzne",
        [](const rectangleArgs& args) {
            for (std::size_t i = 0; i < args.corners.size(); ++i) {
                for (std::size_t j = i + 1; j < args.corners.size(); ++j) {
                    const vector2D& first = args.corners[i];
                    const vector2D& second = args.corners[j];

                    if (first.x == second.x && first.y == second.y) {
                        return false;
                    }
                }
            }

            return true;
        }
    }
};

const schema<rotationArgs> rotationSchema{
    {
        "center",
        "Stred rotace musi mit konecne souradnice",
        [](const rotationArgs& args) {
            return is_valid_vector_2d(args.center);
        }
    },
    {
        "angle",
        "Uhel rotace musi byt konecne cislo",
        [](const rotationArgs& args) {
            return std::isfinite(args.angleDegrees);
        }
    }
};

const schema<scaleArgs> scaleSchema{
    {
        "center",
        "Stred skalovani musi mit konecne souradnice",
        [](const scaleArgs& args) {
            return is_valid_vector_2d(args.center);
        }
    },
    {
        "factor",
        "Faktor skalovani musi byt konecny a nenulovy",
        [](const scaleArgs& args) {
            return std::isfinite(args.factor)
                && args.factor != 0.0;
        }
    }
};
