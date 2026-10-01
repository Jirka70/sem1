#include <writer/writerFactory.hpp>
#include <writer/svgWriter.hpp>
#include <writer/pgmWriter.hpp>
#include <error/applicationError.hpp>

using writerFactory = std::unique_ptr<IWriter> (*)();

template<typename writerType>
std::unique_ptr<IWriter> make_writer_t() {
    return std::make_unique<writerType>();
}

const std::unordered_map<std::string_view, writerFactory> factories{
    {".svg", make_writer_t<SvgWriter>},
    {".pgm", make_writer_t<PgmWriter>}
};

std::unique_ptr<IWriter> create_writer(const std::filesystem::path& output_path) {
    const auto extension = output_path.extension().string();

    if (!factories.contains(extension)) {
        throw ApplicationError{
            exitCode::OUTPUT_ERROR,
            "Nepodporovany vystupni format: " + extension
        };
    }

    const auto factory = factories.find(extension);
    const writerFactory factory_function = factory->second;

    return factory_function();

}