#ifndef SEM1_WRITER_PGM_WRITER_HPP
#define SEM1_WRITER_PGM_WRITER_HPP

#include <writer/iWriter.hpp>

class PgmWriter final : public IWriter {
public:
    void write(const Scene& scene, CanvasSize size, std::ostream& output) const override;
};

#endif