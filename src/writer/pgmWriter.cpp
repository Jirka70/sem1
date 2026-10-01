#include <writer/pgmWriter.hpp>
#include <writer/pgmShapeVisitor.hpp>

#include <scene.hpp>
#include <error/applicationError.hpp>

#include <cstddef>
#include <ostream>
#include <string>

void PgmWriter::write(
    const Scene& scene,
    CanvasSize size,
    std::ostream& output
) const {
    PgmShapeVisitor visitor{size};

    for (const auto& shape : scene.shapes()) {
        shape->accept(visitor);
    }

    output << "P5"
        << std::endl
        << std::to_string(size.width) 
        << ' '
        << std::to_string(size.height)
        << std::endl 
        << "255" 
        << std::endl;

    for (const unsigned char pixel : visitor.pixels()) {
        output.put(static_cast<char>(pixel));
    }

    if (!output) {
        throw ApplicationError{
            exitCode::OUTPUT_ERROR,
            "Chyba pri zapisu PGM vystupu"
        };
    }
}
