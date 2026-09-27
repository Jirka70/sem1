#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <shape/IShape.hpp>
#include <shape/ShapeArgs.hpp>

#include <array>
#include <memory>

class Rectangle final : public IShape {
public:
    Rectangle(RectangleArgs args);
    using Corners = std::array<Vector2D, RECTANGLE_SIDES_COUNT>;

    [[nodiscard]]
    const Corners& corners() const;

    [[nodiscard]]
    std::unique_ptr<IShape> operator+(Vector2D offset) const override;

    [[nodiscard]]
    std::unique_ptr<IShape> operator-(Vector2D offset) const override;

    [[nodiscard]]
    std::unique_ptr<IShape> operator*(Vector2D factors) const override;

    [[nodiscard]]
    std::unique_ptr<IShape> rotate(const Rotation& rotation) const override;

private:
    RectangleArgs args_{};
};

#endif
