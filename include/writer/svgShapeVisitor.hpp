#ifndef SEM1_WRITER_SVG_SHAPE_VISITOR_HPP
#define SEM1_WRITER_SVG_SHAPE_VISITOR_HPP

#include <shape/iShapeVisitor.hpp>

#include <iosfwd>

class SvgShapeVisitor final : public IShapeVisitor {
public:
    explicit SvgShapeVisitor(std::ostream& output);

    void visit(const Circle& circle) override;
    void visit(const Line& line) override;
    void visit(const Rectangle& rectangle) override;

private:
    std::ostream& output_;
};

#endif
