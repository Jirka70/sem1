#ifndef ROTATION_HPP
#define ROTATION_HPP

#include <shape/ShapeArgs.hpp>

class Rotation {
public:
    Rotation(RotationArgs args);

    Vector2D apply(Vector2D point) const;

private:
    RotationArgs args_;
    double cosine_{};
    double sine_{};
};

#endif