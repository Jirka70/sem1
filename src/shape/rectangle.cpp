#include <shape/rectangle.hpp>
#include <shape/iShapeVisitor.hpp>
#include <validation/schema/geometrySchemas.hpp>

Rectangle::Rectangle(RectangleArgs args) : args_(args) {
    require_validation_t(rectangleSchema, args_);
}

void Rectangle::accept(IShapeVisitor& visitor) const {
    visitor.visit(*this);
}

const Rectangle::cornersType& Rectangle::corners() const {
    return args_.corners;
}

std::unique_ptr<IShape> Rectangle::operator+(Vector2D offset) const {
    require_validation_t(vectorSchema, offset);

    RectangleArgs result = args_;

    for (Vector2D& corner : result.corners) {
        corner.x += offset.x;
        corner.y += offset.y;
    }

    return std::make_unique<Rectangle>(result);
}

std::unique_ptr<IShape> Rectangle::operator-(Vector2D offset) const {
    require_validation_t(vectorSchema, offset);
    return *this + Vector2D{-offset.x, -offset.y};
}

std::unique_ptr<IShape> Rectangle::operator*(Vector2D factors) const {
    require_validation_t(scaleFactorsSchema, factors);

    RectangleArgs result = args_;

    for (Vector2D& corner : result.corners) {
        corner.x *= factors.x;
        corner.y *= factors.y;
    }

    return std::make_unique<Rectangle>(result);
}

std::unique_ptr<IShape> Rectangle::rotate(const Rotation& rotation) const {
    RectangleArgs result = args_;

    for (Vector2D& corner : result.corners) {
        corner = rotation.apply(corner);
    }

    return std::make_unique<Rectangle>(result);
}
