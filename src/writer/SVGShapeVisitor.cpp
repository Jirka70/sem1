#include <writer/SVGShapeVisitor.hpp>

#include <error/ApplicationError.hpp>
#include <shape/Circle.hpp>
#include <shape/Line.hpp>
#include <shape/Rectangle.hpp>

#include <array>
#include <charconv>
#include <cmath>
#include <ostream>
#include <string>
#include <system_error>
#include <validation/schema/svgNumberSchema.hpp>

constexpr std::size_t SCIENTIFIC_NOTATION_OVERHEAD = 7;

constexpr std::size_t NUMBER_BUFFER_SIZE = std::numeric_limits<double>::max_digits10 + SCIENTIFIC_NOTATION_OVERHEAD;

static std::string svg_number(double value) {
    require_validation(svgNumberSchema, value);

    std::array<char, NUMBER_BUFFER_SIZE> buffer{};
    const auto [end, error] = std::to_chars(
        buffer.data(), buffer.data() + buffer.size(), value
    );

    if (error != std::errc{}) {
        throw ApplicationError{ExitCode::output_error,
            "Nelze prevest cislo pro SVG vystup"};
    }

    return std::string(buffer.data(), end);
}

SVGShapeVisitor::SVGShapeVisitor(std::ostream& output) : output_(output) {}

void SVGShapeVisitor::visit(const Circle& circle) {
    const Vector2D center = circle.center();
    output_ << "    <circle cx=\"" << svg_number(center.x)
            << "\" cy=\"" << svg_number(center.y)
            << "\" r=\"" << svg_number(circle.radius()) << "\" />" << std::endl;
}

void SVGShapeVisitor::visit(const Line& line) {
    const Vector2D start = line.start();
    const Vector2D end = line.end();
    output_ << "    <line x1=\"" << svg_number(start.x)
            << "\" y1=\"" << svg_number(start.y)
            << "\" x2=\"" << svg_number(end.x)
            << "\" y2=\"" << svg_number(end.y) << "\" />" << std::endl;
}

void SVGShapeVisitor::visit(const Rectangle& rectangle) {
    // A transformed rectangle need not be aligned with the canvas axes.
    output_ << "    <polygon points=\"";
    bool first = true;
    for (const Vector2D& corner : rectangle.corners()) {
        if (!first) {
            output_ << ' ';
        }
        output_ << svg_number(corner.x) << ',' << svg_number(corner.y);
        first = false;
    }
    output_ << "\" />" << std::endl;
}
