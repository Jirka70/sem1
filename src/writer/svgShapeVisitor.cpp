#include <writer/svgShapeVisitor.hpp>

#include <error/applicationError.hpp>
#include <shape/circle.hpp>
#include <shape/line.hpp>
#include <shape/rectangle.hpp>

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
    require_validation_t(svgNumberSchema, value);

    std::array<char, NUMBER_BUFFER_SIZE> buffer{};
    const auto [end, error] = std::to_chars(
        buffer.data(), buffer.data() + buffer.size(), value
    );

    if (error != std::errc{}) {
        throw applicationError{exitCode::OUTPUT_ERROR,
            "Nelze prevest cislo pro SVG vystup"};
    }

    return std::string(buffer.data(), end);
}

svgShapeVisitor::svgShapeVisitor(std::ostream& output) : output_(output) {}

void svgShapeVisitor::visit(const circle& circle) {
    const vector2D center = circle.center();
    output_ << "    <circle cx=\"" << svg_number(center.x)
            << "\" cy=\"" << svg_number(center.y)
            << "\" r=\"" << svg_number(circle.radius()) << "\" />" << std::endl;
}

void svgShapeVisitor::visit(const line& line) {
    const vector2D start = line.start();
    const vector2D end = line.end();
    output_ << "    <line x1=\"" << svg_number(start.x)
            << "\" y1=\"" << svg_number(start.y)
            << "\" x2=\"" << svg_number(end.x)
            << "\" y2=\"" << svg_number(end.y) << "\" />" << std::endl;
}

void svgShapeVisitor::visit(const rectangle& rectangle) {
    // A transformed rectangle need not be aligned with the canvas axes.
    output_ << "    <polygon points=\"";
    bool first = true;
    for (const vector2D& corner : rectangle.corners()) {
        if (!first) {
            output_ << ' ';
        }
        output_ << svg_number(corner.x) << ',' << svg_number(corner.y);
        first = false;
    }
    output_ << "\" />" << std::endl;
}
