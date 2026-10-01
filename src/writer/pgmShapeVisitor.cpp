#include <writer/pgmShapeVisitor.hpp>

#include <error/applicationError.hpp>
#include <shape/circle.hpp>
#include <shape/line.hpp>
#include <shape/rectangle.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <validation/schema/canvasSizeSchema.hpp>

static constexpr unsigned char BLACK = 0;
static constexpr unsigned char WHITE = 255;

static constexpr double STROKE_WIDTH_PX = 2.0;
static constexpr double HALF_STROKE_PX = STROKE_WIDTH_PX / 2.0;
static constexpr double PIXEL_CENTER_OFFSET = 0.5;

pgmShapeVisitor::pgmShapeVisitor(canvasSize size)
    : size_(size) {
    require_validation_t(canvasSizeSchema, size);  

    const auto width = static_cast<std::size_t>(size.width);
    const auto height = static_cast<std::size_t>(size.height);

    if (width > pixels_.max_size() / height) {
        throw applicationError{
            exitCode::OUTPUT_ERROR,
            "Platno je prilis velke pro PGM vystup"
        };
    }

    pixels_.assign(width * height, WHITE);
}

std::span<const unsigned char>
pgmShapeVisitor::pixels() const noexcept {
    return {pixels_.data(), pixels_.size()};
}

pgmShapeVisitor::pixelBounds pgmShapeVisitor::clipped_bounds(
    double left,
    double top,
    double right,
    double bottom
) const {
    const double width = static_cast<double>(size_.width);
    const double height = static_cast<double>(size_.height);

    // Nejprve orezat, az potom prevadet na int.
    return {
        .left = static_cast<int>(
            std::floor(std::clamp(left, 0.0, width))
        ),
        .top = static_cast<int>(
            std::floor(std::clamp(top, 0.0, height))
        ),
        .right = static_cast<int>(
            std::ceil(std::clamp(right, 0.0, width))
        ),
        .bottom = static_cast<int>(
            std::ceil(std::clamp(bottom, 0.0, height))
        )
    };
}

void pgmShapeVisitor::set_black(int x, int y) {
    const auto index =
        static_cast<std::size_t>(y)
        * static_cast<std::size_t>(size_.width)
        + static_cast<std::size_t>(x);

    pixels_[index] = BLACK;
}

void pgmShapeVisitor::visit(const circle& circle) {
    const vector2D center = circle.center();
    const double radius = circle.radius();
    const double extent = radius + HALF_STROKE_PX;

    const pixelBounds bounds = clipped_bounds(
        center.x - extent,
        center.y - extent,
        center.x + extent,
        center.y + extent
    );

    for (int y = bounds.top; y < bounds.bottom; ++y) {
        for (int x = bounds.left; x < bounds.right; ++x) {
            const double pixel_x = x + PIXEL_CENTER_OFFSET;
            const double pixel_y = y + PIXEL_CENTER_OFFSET;

            const double distance = std::hypot(
                pixel_x - center.x,
                pixel_y - center.y
            );

            if (std::abs(distance - radius) <= HALF_STROKE_PX) {
                set_black(x, y);
            }
        }
    }
}

void pgmShapeVisitor::draw_segment(
    vector2D start,
    vector2D end
) {
    const double dx = end.x - start.x;
    const double dy = end.y - start.y;
    const double length = std::hypot(dx, dy);

    if (!std::isfinite(length) || length <= 0.0) {
        throw applicationError{
            exitCode::OUTPUT_ERROR,
            "Usecku nelze rasterizovat: neplatna delka"
        };
    }

    const double direction_x = dx / length;
    const double direction_y = dy / length;

    const pixelBounds bounds = clipped_bounds(
        std::min(start.x, end.x) - HALF_STROKE_PX,
        std::min(start.y, end.y) - HALF_STROKE_PX,
        std::max(start.x, end.x) + HALF_STROKE_PX,
        std::max(start.y, end.y) + HALF_STROKE_PX
    );

    for (int y = bounds.top; y < bounds.bottom; ++y) {
        for (int x = bounds.left; x < bounds.right; ++x) {
            const double pixel_x = x + PIXEL_CENTER_OFFSET;
            const double pixel_y = y + PIXEL_CENTER_OFFSET;

            const double relative_x = pixel_x - start.x;
            const double relative_y = pixel_y - start.y;

            // Vzdalenost projekce od pocatku usecky.
            const double projection =
                relative_x * direction_x
                + relative_y * direction_y;

            // Nejblizsi bod musi lezet mezi obema konci.
            const double along = std::clamp(
                projection,
                0.0,
                length
            );

            const double nearest_x =
                start.x + along * direction_x;

            const double nearest_y =
                start.y + along * direction_y;

            const double distance = std::hypot(
                pixel_x - nearest_x,
                pixel_y - nearest_y
            );

            if (distance <= HALF_STROKE_PX) {
                set_black(x, y);
            }
        }
    }
}

void pgmShapeVisitor::visit(const line& line) {
    draw_segment(line.start(), line.end());
}

void pgmShapeVisitor::visit(const rectangle& rectangle) {
    const auto& corners = rectangle.corners();

    for (std::size_t i = 0; i < corners.size(); ++i) {
        const std::size_t next = (i + 1) % corners.size();

        draw_segment(corners[i], corners[next]);
    }
}