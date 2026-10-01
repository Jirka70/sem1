#include <shape/rectangle.hpp>
#include <shape/iShapeVisitor.hpp>
#include <validation/schema/geometrySchemas.hpp>

rectangle::rectangle(rectangleArgs args) : args_(args) {
    require_validation_t(rectangleSchema, args_);
}

void rectangle::accept(iShapeVisitor& visitor) const {
    visitor.visit(*this);
}

const rectangle::cornersType& rectangle::corners() const {
    return args_.corners;
}

std::unique_ptr<iShape> rectangle::operator+(vector2D offset) const {
    require_validation_t(vectorSchema, offset);

    rectangleArgs result = args_;

    for (vector2D& corner : result.corners) {
        corner.x += offset.x;
        corner.y += offset.y;
    }

    return std::make_unique<rectangle>(result);
}

std::unique_ptr<iShape> rectangle::operator-(vector2D offset) const {
    require_validation_t(vectorSchema, offset);
    return *this + vector2D{-offset.x, -offset.y};
}

std::unique_ptr<iShape> rectangle::operator*(vector2D factors) const {
    require_validation_t(scaleFactorsSchema, factors);

    rectangleArgs result = args_;

    for (vector2D& corner : result.corners) {
        corner.x *= factors.x;
        corner.y *= factors.y;
    }

    return std::make_unique<rectangle>(result);
}

std::unique_ptr<iShape> rectangle::rotate(const rotation& rotation) const {
    rectangleArgs result = args_;

    for (vector2D& corner : result.corners) {
        corner = rotation.apply(corner);
    }

    return std::make_unique<rectangle>(result);
}
