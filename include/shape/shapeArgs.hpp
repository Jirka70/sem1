#ifndef SEM1_SHAPE_SHAPE_ARGS_HPP
#define SEM1_SHAPE_SHAPE_ARGS_HPP

#include <array>
#include <cstddef>


struct vector2D {
    double x;
    double y;
};

struct circleArgs {
    vector2D center;
    double radius;
};

struct lineArgs {
    vector2D start;
    vector2D end;
};

inline constexpr std::size_t RECTANGLE_SIDES_COUNT = 4;

struct rectangleArgs {
    std::array<vector2D, RECTANGLE_SIDES_COUNT> corners;
};

struct rotationArgs {
    vector2D center;
    double angleDegrees;
};

struct scaleArgs {
    vector2D center;
    double factor;
};

#endif
