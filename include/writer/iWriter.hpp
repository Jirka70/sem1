#ifndef SEM1_WRITER_I_WRITER_HPP
#define SEM1_WRITER_I_WRITER_HPP

#include <writer/canvasSize.hpp>

#include <iosfwd>

class scene;

class iWriter {
public:
    virtual ~iWriter() = default;

    virtual void write(
        const scene& scene,
        canvasSize size,
        std::ostream& output
    ) const = 0;
};

#endif
