#ifndef SEM1_SHAPE_RECTANGLE_HPP
#define SEM1_SHAPE_RECTANGLE_HPP

#include <shape/iShape.hpp>
#include <shape/shapeArgs.hpp>

#include <array>
#include <memory>

class rectangle final : public iShape {
public:
    explicit rectangle(rectangleArgs args);

    void accept(iShapeVisitor& visitor) const override;
    using cornersType = std::array<vector2D, RECTANGLE_SIDES_COUNT>;

    const cornersType& corners() const;

    std::unique_ptr<iShape> operator+(vector2D offset) const override;

    std::unique_ptr<iShape> operator-(vector2D offset) const override;

    std::unique_ptr<iShape> operator*(vector2D factors) const override;

    std::unique_ptr<iShape> rotate(const rotation& rotation) const override;

private:
    rectangleArgs args_{};
};

#endif
