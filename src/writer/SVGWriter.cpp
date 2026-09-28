#include <writer/SVGWriter.hpp>

#include <Scene.hpp>
#include <error/ApplicationError.hpp>
#include <shape/Circle.hpp>
#include <shape/IShapeVisitor.hpp>
#include <shape/Line.hpp>
#include <shape/Rectangle.hpp>

#include <array>
#include <charconv>
#include <cmath>
#include <ostream>
#include <stdexcept>
#include <string>
#include <system_error>

namespace {

// Shortest round-trippable representation, independent of the stream locale.
std::string svg_number(double value) {
    if (!std::isfinite(value)) {
        throw ApplicationError{ExitCode::output_error,
            "SVG souradnice musi byt konecne cislo"};
    }

    std::array<char, 128> buffer{};
    const auto [end, error] = std::to_chars(
        buffer.data(), buffer.data() + buffer.size(), value
    );

    if (error != std::errc{}) {
        throw ApplicationError{ExitCode::output_error,
            "Nelze prevest cislo pro SVG vystup"};
    }

    return std::string(buffer.data(), end);
}

class SVGShapeVisitor final : public IShapeVisitor {
public:
    explicit SVGShapeVisitor(std::ostream& output);

    void visit(const Circle& circle) override;
    void visit(const Line& line) override;
    void visit(const Rectangle& rectangle) override;

private:
    std::ostream& output_;
};

SVGShapeVisitor::SVGShapeVisitor(std::ostream& output) : output_(output) {}

void SVGShapeVisitor::visit(const Circle& circle) {
    const Vector2D center = circle.center();
    output_ << "    <circle cx=\"" << svg_number(center.x)
            << "\" cy=\"" << svg_number(center.y)
            << "\" r=\"" << svg_number(circle.radius()) << "\" />\n";
}

void SVGShapeVisitor::visit(const Line& line) {
    const Vector2D start = line.start();
    const Vector2D end = line.end();
    output_ << "    <line x1=\"" << svg_number(start.x)
            << "\" y1=\"" << svg_number(start.y)
            << "\" x2=\"" << svg_number(end.x)
            << "\" y2=\"" << svg_number(end.y) << "\" />\n";
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
    output_ << "\" />\n";
}

}

void SVGWriter::write(
    const Scene& scene,
    CanvasSize size,
    std::ostream& output
) const {
    if (size.width <= 0 || size.height <= 0) {
        throw std::invalid_argument{"Rozmery platna musi byt kladne"};
    }

    const std::string width = std::to_string(size.width);
    const std::string height = std::to_string(size.height);

    output << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
           << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width
           << "\" height=\"" << height
           << "\" viewBox=\"0 0 " << width << ' ' << height
           << "\" overflow=\"hidden\">\n"
           << "  <rect width=\"100%\" height=\"100%\" fill=\"white\" />\n"
           << "  <g fill=\"none\" stroke=\"black\" stroke-width=\"2\""
              " stroke-linecap=\"round\" stroke-linejoin=\"round\">\n";

    SVGShapeVisitor visitor{output};
    for (const auto& shape : scene.shapes()) {
        shape->accept(visitor);
    }

    output << "  </g>\n</svg>\n";
    if (!output) {
        throw ApplicationError{ExitCode::output_error,
            "Chyba pri zapisu SVG vystupu"};
    }
}
