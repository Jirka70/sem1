#ifndef SEM1_SHAPE_CIRCLE_HPP
#define SEM1_SHAPE_CIRCLE_HPP

#include <shape/iShape.hpp>
#include <shape/shapeArgs.hpp>

#include <memory>

class circle final : public iShape {
public:
    explicit circle(circleArgs args);

    void accept(iShapeVisitor& visitor) const override;

    vector2D center() const;

    double radius() const;

    std::unique_ptr<iShape> operator+(vector2D offset) const override;

    std::unique_ptr<iShape> operator-(vector2D offset) const override;

    std::unique_ptr<iShape> operator*(vector2D factors) const override;

    std::unique_ptr<iShape> rotate(const rotation& rotation) const override;

private:
    circleArgs args_{};
};

#endif
