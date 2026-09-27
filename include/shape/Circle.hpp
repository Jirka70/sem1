#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <shape/IShape.hpp>
#include <validation/Validation.hpp>
#include <validation/schema/geometrySchemas.hpp>

#include <cmath>
#include <memory>
#include <stdexcept>

class Circle final : public IShape {
public:
    explicit Circle(CircleArgs args)
        : args_(args) {
        require_validation(circleSchema, args_);
    }

    Circle(Vector2D center, double radius)
        : Circle(CircleArgs{center, radius}) {
    }

    [[nodiscard]]
    Vector2D center() const noexcept {
        return args_.center;
    }

    [[nodiscard]]
    double radius() const noexcept {
        return args_.radius;
    }

    [[nodiscard]]
    std::unique_ptr<IShape> operator+(
        Vector2D offset
    ) const override {
        require_validation(vectorSchema, offset);

        return std::make_unique<Circle>(
            geometry::translate(args_.center, offset),
            args_.radius
        );
    }

    [[nodiscard]]
    std::unique_ptr<IShape> operator-(
        Vector2D offset
    ) const override {
        return *this + geometry::negate(offset);
    }

    [[nodiscard]]
    std::unique_ptr<IShape> operator*(
        Vector2D factors
    ) const override {
        require_validation(scaleFactorsSchema, factors);

        const double xScale = std::abs(factors.x);
        const double yScale = std::abs(factors.y);

        if (xScale != yScale) {
            throw std::invalid_argument{
                "Kruh vyzaduje stejnou absolutni velikost "
                "meritka v obou osach"
            };
        }

        return std::make_unique<Circle>(
            geometry::scale(args_.center, factors),
            args_.radius * xScale
        );
    }

    [[nodiscard]]
    std::unique_ptr<IShape> rotate(
        const Rotation& rotation
    ) const override {
        return std::make_unique<Circle>(
            rotation.apply(args_.center),
            args_.radius
        );
    }

private:
    CircleArgs args_;
};

#endif