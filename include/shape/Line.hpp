#ifndef LINE_HPP
#define LINE_HPP

#include <shape/IShape.hpp>
#include <shape/ShapeArgs.hpp>

#include <memory>

class Line final : public IShape {
public:
    Line(LineArgs args);

    void accept(IShapeVisitor& visitor) const override;

    Vector2D start() const;

    Vector2D end() const;

    std::unique_ptr<IShape> operator+(Vector2D offset) const override;

    std::unique_ptr<IShape> operator-(Vector2D offset) const override;

    std::unique_ptr<IShape> operator*(Vector2D factors) const override;

    std::unique_ptr<IShape> rotate(const Rotation& rotation) const override;

private:
    LineArgs args_{};
};

#endif
