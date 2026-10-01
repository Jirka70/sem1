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

    output << "P5"
        << std::endl
        << std::to_string(size.width) << ' '
        << std::to_string(size.height)
        << std::endl << "255" << std::endl;

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
