#ifndef SEM1_WRITER_I_WRITER_HPP
#define SEM1_WRITER_I_WRITER_HPP

#include <writer/canvasSize.hpp>

#include <iosfwd>

class Scene;

class IWriter {
public:
    virtual ~IWriter() = default;

    virtual void write(
        const Scene& scene,
        CanvasSize size,
        std::ostream& output
    ) const = 0;
};

#endif
