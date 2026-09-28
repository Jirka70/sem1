#ifndef SVG_SHAPE_VISITOR_HPP
#define SVG_SHAPE_VISITOR_HPP

#include <shape/IShapeVisitor.hpp>

#include <iosfwd>

class SVGShapeVisitor final : public IShapeVisitor {
public:
    explicit SVGShapeVisitor(std::ostream& output);

    void visit(const Circle& circle) override;
    void visit(const Line& line) override;
    void visit(const Rectangle& rectangle) override;

private:
    std::ostream& output_;
};

#endif
