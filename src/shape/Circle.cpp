#include <shape/Circle.hpp>
#include <validation/schema/geometrySchemas.hpp>

Circle::Circle(CircleArgs args) : args_(args) {
    require_validation(circleSchema, args_);
}

Vector2D Circle::center() const {
    return args_.center;
}

double Circle::radius() const {
    return args_.radius;
}

std::unique_ptr<IShape> Circle::operator+(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Circle::operator-(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Circle::operator*(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Circle::rotate(const Rotation&) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}
