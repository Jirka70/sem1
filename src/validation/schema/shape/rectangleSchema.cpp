#include <validation/schema/shape/rectangleSchema.hpp>

#include <cmath>
#include <cstddef>

const Schema<Rectangle> rectangleSchema{
    {
        "corners",
        "Souradnice vrcholu musi byt konecna cisla",
        [](const Rectangle& args) {
            for (const Point& point : args.corners) {
                if (!std::isfinite(point.x)
                    || !std::isfinite(point.y)) {
                    return false;
                }
            }

            return true;
        }
    },
    {
        "corners",
        "Vsechny ctyri vrcholy musi byt navzajem ruzne",
        [](const Rectangle& args) {
            for (std::size_t i = 0; i < args.corners.size(); ++i) {
                for (std::size_t j = i + 1; j < args.corners.size(); ++j) {
                    const Point& first = args.corners[i];
                    const Point& second = args.corners[j];

                    if (first.x == second.x && first.y == second.y) {
                        return false;
                    }
                }
            }

            return true;
        }
    },
    {
        "corners",
        "Pocet vrcholu musi byt presne 4",
        [](const Rectangle& args) {
            return args.corners.size() == RECTANGLE_SIDES_COUNT;
        }
    },
};