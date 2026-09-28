#ifndef SVG_WRITER_HPP
#define SVG_WRITER_HPP

#include <writer/IWriter.hpp>

class SVGWriter final : public IWriter {
public:
    void write(
        const Scene& scene,
        CanvasSize size,
        std::ostream& output
    ) const override;
};

#endif
