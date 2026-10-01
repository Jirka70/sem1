#ifndef SEM1_WRITER_SVG_WRITER_HPP
#define SEM1_WRITER_SVG_WRITER_HPP

#include <writer/iWriter.hpp>

class SvgWriter final : public IWriter {
public:
    void write(
        const Scene& scene,
        CanvasSize size,
        std::ostream& output
    ) const override;
};

#endif
