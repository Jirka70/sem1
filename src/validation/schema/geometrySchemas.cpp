#include <validation/schema/geometrySchemas.hpp>

#include <cmath>
#include <cstddef>



const schema<Vector2D> vectorSchema{
    {
        "vector",
        "Slozky vektoru musi byt konecna cisla",
        [](const Vector2D& vector) {
            return std::isfinite(vector.x)
                && std::isfinite(vector.y);
        }
    }
};

bool is_valid_vector_2d(const Vector2D& vec) {
    return !validate_t(vectorSchema, vec).has_value();
}


const schema<Vector2D> scaleFactorsSchema{
    {
        "scale",
        "Meritka musi byt konecna nenulova cisla",
        [](const Vector2D& factors) {
            return is_valid_vector_2d(factors)
                && factors.x != 0.0
                && factors.y != 0.0;
        }
    }
};

const schema<CircleArgs> circleSchema{
    {
        "center",
        "Souradnice stredu musi byt konecna cisla",
        [](const CircleArgs& args) {
            return is_valid_vector_2d(args.center);
        }
    },
    {
        "radius",
        "Polomer musi byt konecne cislo vetsi nez nula",
        [](const CircleArgs& args) {
            return std::isfinite(args.radius)
                && args.radius > 0.0;
        }
    }
};

const schema<LineArgs> lineSchema{
    {
        "start",
        "Pocatecni bod musi mit konecne souradnice",
        [](const LineArgs& args) {
            return is_valid_vector_2d(args.start);
        }
    },
    {
        "end",
        "Koncovy bod musi mit konecne souradnice",
        [](const LineArgs& args) {
            return is_valid_vector_2d(args.end);
        }
    },
    {
        "points",
        "Pocatecni a koncovy bod nesmi byt totozne",
        [](const LineArgs& args) {
            return args.start.x != args.end.x
                || args.start.y != args.end.y;
        }
    }
};

const schema<RectangleArgs> rectangleSchema{
    {
        "corners",
        "Vrcholy musi mit konecne souradnice",
        [](const RectangleArgs& args) {
            for (const Vector2D corner : args.corners) {
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
        [](const RectangleArgs& args) {
            for (std::size_t i = 0; i < args.corners.size(); ++i) {
                for (std::size_t j = i + 1; j < args.corners.size(); ++j) {
                    const Vector2D& first = args.corners[i];
                    const Vector2D& second = args.corners[j];

                    if (first.x == second.x && first.y == second.y) {
                        return false;
                    }
                }
            }

            return true;
        }
    }
};

const schema<RotationArgs> rotationSchema{
    {
        "center",
        "Stred rotace musi mit konecne souradnice",
        [](const RotationArgs& args) {
            return is_valid_vector_2d(args.center);
        }
    },
    {
        "angle",
        "Uhel rotace musi byt konecne cislo",
        [](const RotationArgs& args) {
            return std::isfinite(args.angleDegrees);
        }
    }
};

const schema<ScaleArgs> scaleSchema{
    {
        "center",
        "Stred skalovani musi mit konecne souradnice",
        [](const ScaleArgs& args) {
            return is_valid_vector_2d(args.center);
        }
    },
    {
        "factor",
        "Faktor skalovani musi byt konecny a nenulovy",
        [](const ScaleArgs& args) {
            return std::isfinite(args.factor)
                && args.factor != 0.0;
        }
    }
};
