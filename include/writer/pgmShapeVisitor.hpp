#ifndef SEM1_WRITER_PGM_SHAPE_VISITOR_HPP
#define SEM1_WRITER_PGM_SHAPE_VISITOR_HPP

#include <shape/iShapeVisitor.hpp>
#include <shape/shapeArgs.hpp>
#include <writer/canvasSize.hpp>

#include <span>
#include <vector>

class PgmShapeVisitor final : public IShapeVisitor {
public:
    explicit PgmShapeVisitor(CanvasSize size);

    void visit(const Circle& circle) override;
    void visit(const Line& line) override;
    void visit(const Rectangle& rectangle) override;

    std::span<const unsigned char> pixels() const noexcept;

private:
    struct PixelBounds {
        int left;
        int top;
        int right;
        int bottom;
    };

    PixelBounds clipped_bounds(
        double left,
        double top,
        double right,
        double bottom
    ) const;

    void set_black(int x, int y);

    void draw_segment(Vector2D start, Vector2D end);

    CanvasSize size_;
    std::vector<unsigned char> pixels_;
};

#endif