#include <writer/SVGWriter.hpp>
#include <writer/SVGShapeVisitor.hpp>

#include <Scene.hpp>
#include <error/ApplicationError.hpp>

#include <ostream>
#include <stdexcept>
#include <string>

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
