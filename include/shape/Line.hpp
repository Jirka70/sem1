#ifndef LINE_HPP
#define LINE_HPP

#include <shape/IShape.hpp>
#include <shape/ShapeArgs.hpp>

#include <memory>

class Line final : public IShape {
public:
    Line(LineArgs args);

    [[nodiscard]]
    Vector2D start() const;

    [[nodiscard]]
    Vector2D end() const;

    [[nodiscard]]
    std::unique_ptr<IShape> operator+(Vector2D offset) const override;

    [[nodiscard]]
    std::unique_ptr<IShape> operator-(Vector2D offset) const override;

    [[nodiscard]]
    std::unique_ptr<IShape> operator*(Vector2D factors) const override;

    [[nodiscard]]
    std::unique_ptr<IShape> rotate(const Rotation& rotation) const override;

private:
    LineArgs args_{};
};

#endif
