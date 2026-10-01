#include <shape/Circle.hpp>
#include <shape/IShapeVisitor.hpp>
#include <validation/schema/geometrySchemas.hpp>

Circle::Circle(CircleArgs args) : args_(args) {
    require_validation(circleSchema, args_);
}

void Circle::accept(IShapeVisitor& visitor) const {
    visitor.visit(*this);
}

Vector2D Circle::center() const {
    return args_.center;
}

double Circle::radius() const {
    return args_.radius;
}

std::unique_ptr<IShape> Circle::operator+(Vector2D offset) const {
    require_validation(vectorSchema, offset);

    const CircleArgs result{
        .center = {
            .x = args_.center.x + offset.x,
            .y = args_.center.y + offset.y
        },
        .radius = args_.radius
    };

    return std::make_unique<Circle>(result);
}

std::unique_ptr<IShape> Circle::operator-(Vector2D offset) const {
    require_validation(vectorSchema, offset);
    return *this + Vector2D{-offset.x, -offset.y};
}

std::unique_ptr<IShape> Circle::operator*(Vector2D factors) const {
    require_validation(vectorSchema, factors);
    const double xScale = std::abs(factors.x);
    const double yScale = std::abs(factors.y);

    if (xScale != yScale) {
        throw std::invalid_argument{
            "Kruh vyzaduje stejnou absolutni velikost "
            "meritka v obou osach"
        };
    }

    const CircleArgs result{
        .center = {
            .x = args_.center.x * factors.x,
            .y = args_.center.y * factors.y
        },
        .radius = args_.radius * xScale
    };

    return std::make_unique<Circle>(result);
}

std::unique_ptr<IShape> Circle::rotate(const Rotation& rotation) const {
   const CircleArgs result{
        .center = rotation.apply(args_.center),
        .radius = args_.radius
    };

    return std::make_unique<Circle>(result);
}
