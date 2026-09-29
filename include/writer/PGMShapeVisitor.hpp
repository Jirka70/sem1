#ifndef PGM_SHAPE_VISITOR_HPP
#define PGM_SHAPE_VISITOR_HPP

#include <shape/IShapeVisitor.hpp>
#include <shape/ShapeArgs.hpp>
#include <writer/CanvasSize.hpp>

#include <span>
#include <vector>

class PGMShapeVisitor final : public IShapeVisitor {
public:
    explicit PGMShapeVisitor(CanvasSize size);

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