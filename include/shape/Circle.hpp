#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <shape/IShape.hpp>
#include <shape/ShapeArgs.hpp>

#include <memory>

class Circle final : public IShape {
public:
    Circle(CircleArgs args);

    void accept(IShapeVisitor& visitor) const override;

    Vector2D center() const;

    double radius() const;

    std::unique_ptr<IShape> operator+(Vector2D offset) const override;

    std::unique_ptr<IShape> operator-(Vector2D offset) const override;

    std::unique_ptr<IShape> operator*(Vector2D factors) const override;

    std::unique_ptr<IShape> rotate(const Rotation& rotation) const override;

private:
    CircleArgs args_{};
};

#endif
