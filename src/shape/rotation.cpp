#include <shape/rotation.hpp>
#include <validation/validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

#include <cmath>
#include <numbers>

Rotation::Rotation(RotationArgs args)
    : args_(args) {
    require_validation_t(rotationSchema, args_);

    constexpr double FULL_TURN_DEGREES = 360.0;
    constexpr double HALF_TURN_DEGREES = 180.0;

    const double normalizedAngle =
        std::remainder(
            args_.angleDegrees,
            FULL_TURN_DEGREES
        );

    const double radians =
        normalizedAngle
        * (std::numbers::pi / HALF_TURN_DEGREES);

    cosine_ = std::cos(radians);
    sine_ = std::sin(radians);
}

Vector2D Rotation::apply(Vector2D point) const {
    require_validation_t(vectorSchema, point);

    const double relativeX = point.x - args_.center.x;
    const double relativeY = point.y - args_.center.y;

    const Vector2D result{
        .x = args_.center.x
            + relativeX * cosine_
            - relativeY * sine_,

        .y = args_.center.y
            + relativeX * sine_
            + relativeY * cosine_
    };

    return result;
}