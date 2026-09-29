#ifndef PGM_WRITER_HPP
#define PGM_WRITER_HPP

#include <writer/IWriter.hpp>

class PGMWriter final : public IWriter {
public:
    void write(const Scene& scene, CanvasSize size, std::ostream& output) const override;
};

#endif