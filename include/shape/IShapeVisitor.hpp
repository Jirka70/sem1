#ifndef I_SHAPE_VISITOR_HPP
#define I_SHAPE_VISITOR_HPP

class Circle;
class Line;
class Rectangle;

class IShapeVisitor {
public:
    virtual ~IShapeVisitor() = default;

    virtual void visit(const Circle& circle) = 0;
    virtual void visit(const Line& line) = 0;
    virtual void visit(const Rectangle& rectangle) = 0;
};

#endif
