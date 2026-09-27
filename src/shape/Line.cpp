#include <shape/Line.hpp>
#include <validation/schema/geometrySchemas.hpp>

Line::Line(LineArgs args) : args_(args) {
    require_validation(lineSchema, args_);
}

Vector2D Line::start() const {
    return args_.start;
}

Vector2D Line::end() const {
    return args_.end;
}

std::unique_ptr<IShape> Line::operator+(Vector2D offset) const {
    require_validation(vectorSchema, offset);

    const LineArgs result{
        .start = {
            .x = args_.start.x + offset.x,
            .y = args_.start.y + offset.y
        },
        .end = {
            .x = args_.end.x + offset.x,
            .y = args_.end.y + offset.y
        }
    };

    return std::make_unique<Line>(result);
}

std::unique_ptr<IShape> Line::operator-(Vector2D offset) const {
    require_validation(vectorSchema, offset);
    return *this + Vector2D{-offset.x, -offset.y};
}

std::unique_ptr<IShape> Line::operator*(Vector2D factors) const {
    require_validation(scaleFactorsSchema, factors);

    const LineArgs result{
        .start = {
            .x = args_.start.x * factors.x,
            .y = args_.start.y * factors.y
        },
        .end = {
            .x = args_.end.x * factors.x,
            .y = args_.end.y * factors.y
        }
    };

    return std::make_unique<Line>(result);
}

std::unique_ptr<IShape> Line::rotate(const Rotation& rotation) const {
    const LineArgs result{
        .start = rotation.apply(args_.start),
        .end = rotation.apply(args_.end)
    };

    return std::make_unique<Line>(result);
}
