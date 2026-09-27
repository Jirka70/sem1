#include <shape/Line.hpp>
#include <validation/schema/geometrySchemas.hpp>

Line::Line(LineArgs args) : args_(args) {
    require_validation(lineSchema, args_);
    // TODO: Doplnit implementaci.
}

Vector2D Line::start() const {
    return args_.start;
}

Vector2D Line::end() const {
    return args_.end;
}

std::unique_ptr<IShape> Line::operator+(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Line::operator-(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Line::operator*(Vector2D) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}

std::unique_ptr<IShape> Line::rotate(const Rotation&) const {
    // TODO: Doplnit implementaci.
    return nullptr;
}
