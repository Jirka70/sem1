#ifndef I_WRITER_HPP
#define I_WRITER_HPP

#include <writer/CanvasSize.hpp>

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
