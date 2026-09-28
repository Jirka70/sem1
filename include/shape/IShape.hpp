#ifndef I_SHAPE_HPP
#define I_SHAPE_HPP

#include <shape/ShapeArgs.hpp>
#include <shape/Rotation.hpp>

#include <memory>

class IShapeVisitor;

class IShape {
public:
    virtual ~IShape() = default;

    virtual void accept(IShapeVisitor& visitor) const = 0;

    virtual std::unique_ptr<IShape> operator+(
        Vector2D offset
    ) const = 0;

    virtual std::unique_ptr<IShape> operator-(
        Vector2D offset
    ) const = 0;

    virtual std::unique_ptr<IShape> operator*(
        Vector2D factors
    ) const = 0;

    virtual std::unique_ptr<IShape> rotate(
        const Rotation& rotation
    ) const = 0;
};

#endif
