#include <writer/PGMWriter.hpp>
#include <writer/PGMShapeVisitor.hpp>

#include <Scene.hpp>
#include <error/ApplicationError.hpp>

#include <cstddef>
#include <ostream>
#include <string>

void PGMWriter::write(
    const Scene& scene,
    CanvasSize size,
    std::ostream& output
) const {
    PGMShapeVisitor visitor{size};

    for (const auto& shape : scene.shapes()) {
        shape->accept(visitor);
    }

    output << "P5\n"
           << std::to_string(size.width) << ' '
           << std::to_string(size.height)
           << "\n255\n";

    for (const unsigned char pixel : visitor.pixels()) {
        output.put(static_cast<char>(pixel));
    }

    if (!output) {
        throw ApplicationError{
            ExitCode::output_error,
            "Chyba pri zapisu PGM vystupu"
        };
    }
}