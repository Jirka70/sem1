#ifndef SEM1_SHAPE_ROTATION_HPP
#define SEM1_SHAPE_ROTATION_HPP

#include <shape/shapeArgs.hpp>

class Rotation {
public:
    explicit Rotation(RotationArgs args);

    Vector2D apply(Vector2D point) const;

private:
    RotationArgs args_;
    double cosine_{};
    double sine_{};
};

#endif
