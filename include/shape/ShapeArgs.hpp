#ifndef SHAPE_ARGS_HPP
#define SHAPE_ARGS_HPP

#include <array>
#include <cstddef>


struct Vector2D {
    double x;
    double y;
};

struct CircleArgs {
    Vector2D center;
    double radius;
};

struct LineArgs {
    Vector2D start;
    Vector2D end;
};

inline constexpr std::size_t RECTANGLE_SIDES_COUNT = 4;

struct RectangleArgs {
    std::array<Vector2D, RECTANGLE_SIDES_COUNT> corners;
};

struct RotationArgs {
    Vector2D center;
    double angleDegrees;
};

struct ScaleArgs {
    Vector2D center;
    double factor;
};

#endif
