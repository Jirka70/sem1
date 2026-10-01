#ifndef SEM1_WRITER_PGM_WRITER_HPP
#define SEM1_WRITER_PGM_WRITER_HPP

#include <writer/iWriter.hpp>

class pgmWriter final : public iWriter {
public:
    void write(const scene& scene, canvasSize size, std::ostream& output) const override;
};

#endif