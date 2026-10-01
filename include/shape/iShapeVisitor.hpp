#ifndef SEM1_SHAPE_I_SHAPE_VISITOR_HPP
#define SEM1_SHAPE_I_SHAPE_VISITOR_HPP

class circle;
class line;
class rectangle;

class iShapeVisitor {
public:
    virtual ~iShapeVisitor() = default;

    virtual void visit(const circle& circle) = 0;
    virtual void visit(const line& line) = 0;
    virtual void visit(const rectangle& rectangle) = 0;
};

#endif
