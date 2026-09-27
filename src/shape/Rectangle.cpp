#include <shape/Rectangle.hpp>
#include <validation/schema/geometrySchemas.hpp>

Rectangle::Rectangle(RectangleArgs args) : args_(args) {
    require_validation(rectangleSchema, args_);
}

const Rectangle::Corners& Rectangle::corners() const {
    // TODO: Doplnit implementaci.
    return args_.corners;
}

std::unique_ptr<IShape> Rectangle::operator+(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Rectangle::operator-(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Rectangle::operator*(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Rectangle::rotate(const Rotation&) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}
