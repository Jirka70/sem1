#ifndef SEM1_SHAPE_I_SHAPE_HPP
#define SEM1_SHAPE_I_SHAPE_HPP

#include <shape/shapeArgs.hpp>
#include <shape/rotation.hpp>

#include <memory>

class iShapeVisitor;

class iShape {
public:
    virtual ~iShape() = default;

    virtual void accept(iShapeVisitor& visitor) const = 0;

    virtual std::unique_ptr<iShape> operator+(
        vector2D offset
    ) const = 0;

    virtual std::unique_ptr<iShape> operator-(
        vector2D offset
    ) const = 0;

    virtual std::unique_ptr<iShape> operator*(
        vector2D factors
    ) const = 0;

    virtual std::unique_ptr<iShape> rotate(
        const rotation& rotation
    ) const = 0;
};

#endif
