#ifndef SEM1_WRITER_PGM_SHAPE_VISITOR_HPP
#define SEM1_WRITER_PGM_SHAPE_VISITOR_HPP

#include <shape/iShapeVisitor.hpp>
#include <shape/shapeArgs.hpp>
#include <writer/canvasSize.hpp>

#include <span>
#include <vector>

class pgmShapeVisitor final : public iShapeVisitor {
public:
    explicit pgmShapeVisitor(canvasSize size);

    void visit(const circle& circle) override;
    void visit(const line& line) override;
    void visit(const rectangle& rectangle) override;

    std::span<const unsigned char> pixels() const noexcept;

private:
    struct pixelBounds {
        int left;
        int top;
        int right;
        int bottom;
    };

    pixelBounds clipped_bounds(
        double left,
        double top,
        double right,
        double bottom
    ) const;

    void set_black(int x, int y);

    void draw_segment(vector2D start, vector2D end);

    canvasSize size_;
    std::vector<unsigned char> pixels_;
};

#endif