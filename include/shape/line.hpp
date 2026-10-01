#ifndef SEM1_SHAPE_LINE_HPP
#define SEM1_SHAPE_LINE_HPP

#include <shape/iShape.hpp>
#include <shape/shapeArgs.hpp>

#include <memory>

class line final : public iShape {
public:
    explicit line(lineArgs args);

    void accept(iShapeVisitor& visitor) const override;

    vector2D start() const;

    vector2D end() const;

    std::unique_ptr<iShape> operator+(vector2D offset) const override;

    std::unique_ptr<iShape> operator-(vector2D offset) const override;

    std::unique_ptr<iShape> operator*(vector2D factors) const override;

    std::unique_ptr<iShape> rotate(const rotation& rotation) const override;

private:
    lineArgs args_{};
};

#endif
