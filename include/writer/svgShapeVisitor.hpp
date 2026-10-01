#ifndef SEM1_WRITER_SVG_SHAPE_VISITOR_HPP
#define SEM1_WRITER_SVG_SHAPE_VISITOR_HPP

#include <shape/iShapeVisitor.hpp>

#include <iosfwd>

class svgShapeVisitor final : public iShapeVisitor {
public:
    explicit svgShapeVisitor(std::ostream& output);

    void visit(const circle& circle) override;
    void visit(const line& line) override;
    void visit(const rectangle& rectangle) override;

private:
    std::ostream& output_;
};

#endif
