#include <shape/line.hpp>
#include <shape/iShapeVisitor.hpp>
#include <validation/schema/geometrySchemas.hpp>

line::line(lineArgs args) : args_(args) {
    require_validation_t(lineSchema, args_);
}

void line::accept(iShapeVisitor& visitor) const {
    visitor.visit(*this);
}

vector2D line::start() const {
    return args_.start;
}

vector2D line::end() const {
    return args_.end;
}

std::unique_ptr<iShape> line::operator+(vector2D offset) const {
    require_validation_t(vectorSchema, offset);

    const lineArgs result{
        .start = {
            .x = args_.start.x + offset.x,
            .y = args_.start.y + offset.y
        },
        .end = {
            .x = args_.end.x + offset.x,
            .y = args_.end.y + offset.y
        }
    };

    return std::make_unique<line>(result);
}

std::unique_ptr<iShape> line::operator-(vector2D offset) const {
    require_validation_t(vectorSchema, offset);
    return *this + vector2D{-offset.x, -offset.y};
}

std::unique_ptr<iShape> line::operator*(vector2D factors) const {
    require_validation_t(scaleFactorsSchema, factors);

    const lineArgs result{
        .start = {
            .x = args_.start.x * factors.x,
            .y = args_.start.y * factors.y
        },
        .end = {
            .x = args_.end.x * factors.x,
            .y = args_.end.y * factors.y
        }
    };

    return std::make_unique<line>(result);
}

std::unique_ptr<iShape> line::rotate(const rotation& rotation) const {
    const lineArgs result{
        .start = rotation.apply(args_.start),
        .end = rotation.apply(args_.end)
    };

    return std::make_unique<line>(result);
}
