#include <shape/circle.hpp>
#include <shape/iShapeVisitor.hpp>
#include <validation/schema/geometrySchemas.hpp>

circle::circle(circleArgs args) : args_(args) {
    require_validation_t(circleSchema, args_);
}

void circle::accept(iShapeVisitor& visitor) const {
    visitor.visit(*this);
}

vector2D circle::center() const {
    return args_.center;
}

double circle::radius() const {
    return args_.radius;
}

std::unique_ptr<iShape> circle::operator+(vector2D offset) const {
    require_validation_t(vectorSchema, offset);

    const circleArgs result{
        .center = {
            .x = args_.center.x + offset.x,
            .y = args_.center.y + offset.y
        },
        .radius = args_.radius
    };

    return std::make_unique<circle>(result);
}

std::unique_ptr<iShape> circle::operator-(vector2D offset) const {
    require_validation_t(vectorSchema, offset);
    return *this + vector2D{-offset.x, -offset.y};
}

std::unique_ptr<iShape> circle::operator*(vector2D factors) const {
    require_validation_t(vectorSchema, factors);
    const double xScale = std::abs(factors.x);
    const double yScale = std::abs(factors.y);

    if (xScale != yScale) {
        throw std::invalid_argument{
            "Kruh vyzaduje stejnou absolutni velikost "
            "meritka v obou osach"
        };
    }

    const circleArgs result{
        .center = {
            .x = args_.center.x * factors.x,
            .y = args_.center.y * factors.y
        },
        .radius = args_.radius * xScale
    };

    return std::make_unique<circle>(result);
}

std::unique_ptr<iShape> circle::rotate(const rotation& rotation) const {
   const circleArgs result{
        .center = rotation.apply(args_.center),
        .radius = args_.radius
    };

    return std::make_unique<circle>(result);
}
