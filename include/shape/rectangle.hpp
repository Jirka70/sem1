#ifndef SEM1_SHAPE_RECTANGLE_HPP
#define SEM1_SHAPE_RECTANGLE_HPP

#include <shape/iShape.hpp>
#include <shape/shapeArgs.hpp>

#include <array>
#include <memory>

class Rectangle final : public IShape {
public:
    explicit Rectangle(RectangleArgs args);

    void accept(IShapeVisitor& visitor) const override;
    using cornersType = std::array<Vector2D, RECTANGLE_SIDES_COUNT>;

    const cornersType& corners() const;

    std::unique_ptr<IShape> operator+(Vector2D offset) const override;

    std::unique_ptr<IShape> operator-(Vector2D offset) const override;

    std::unique_ptr<IShape> operator*(Vector2D factors) const override;

    std::unique_ptr<IShape> rotate(const Rotation& rotation) const override;

private:
    RectangleArgs args_{};
};

#endif
