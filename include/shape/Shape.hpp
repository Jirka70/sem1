#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <array>
#include <variant>

struct Point {
    double x;
    double y;
    double radius;
};

struct Line {
    Point start;
    Point end;
};

struct Circle {
    Point center;
    double radius;
};

constexpr int RECTANGLE_SIDES_COUNT{4};

struct Rectangle {
    std::array<Point, RECTANGLE_SIDES_COUNT> corners;
};

using Shape = std::variant<Rectangle, Line, Circle>;

#endif
