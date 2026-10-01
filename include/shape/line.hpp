#ifndef SEM1_SHAPE_LINE_HPP
#define SEM1_SHAPE_LINE_HPP

#include <shape/iShape.hpp>
#include <shape/shapeArgs.hpp>

#include <memory>

class Line final : public IShape {
public:
    explicit Line(LineArgs args);

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
