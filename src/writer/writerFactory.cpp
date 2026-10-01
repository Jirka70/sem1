#include <writer/writerFactory.hpp>
#include <writer/svgWriter.hpp>
#include <writer/pgmWriter.hpp>
#include <error/applicationError.hpp>

using writerFactory = std::unique_ptr<iWriter> (*)();

template<typename writerType>
std::unique_ptr<iWriter> make_writer_t() {
    return std::make_unique<writerType>();
}

const std::unordered_map<std::string_view, writerFactory> factories{
    {".svg", make_writer_t<svgWriter>},
    {".pgm", make_writer_t<pgmWriter>}
};

std::unique_ptr<iWriter> create_writer(const std::filesystem::path& output_path) {
    const auto extension = output_path.extension().string();

    if (!factories.contains(extension)) {
        throw applicationError{
            exitCode::OUTPUT_ERROR,
            "Nepodporovany vystupni format: " + extension
        };
    }

    const auto factory = factories.find(extension);
    const writerFactory factory_function = factory->second;

    return factory_function();

}