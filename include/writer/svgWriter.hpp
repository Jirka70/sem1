#ifndef SEM1_WRITER_SVG_WRITER_HPP
#define SEM1_WRITER_SVG_WRITER_HPP

#include <writer/iWriter.hpp>

class svgWriter final : public iWriter {
public:
    void write(
        const scene& scene,
        canvasSize size,
        std::ostream& output
    ) const override;
};

#endif
