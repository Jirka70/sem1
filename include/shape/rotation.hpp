#ifndef SEM1_SHAPE_ROTATION_HPP
#define SEM1_SHAPE_ROTATION_HPP

#include <shape/shapeArgs.hpp>

class rotation {
public:
    explicit rotation(rotationArgs args);

    vector2D apply(vector2D point) const;

private:
    rotationArgs args_;
    double cosine_{};
    double sine_{};
};

#endif
