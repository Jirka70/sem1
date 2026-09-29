#include <writer/writerFactory.hpp>
#include <writer/SVGWriter.hpp>
#include <writer/PGMWriter.hpp>
#include <error/ApplicationError.hpp>

using WriterFactory = std::unique_ptr<IWriter> (*)();

template<typename Writer>
std::unique_ptr<IWriter> make_writer() {
    return std::make_unique<Writer>();
}

const std::unordered_map<std::string_view, WriterFactory> factories{
    {".svg", make_writer<SVGWriter>},
    {".pgm", make_writer<PGMWriter>}
};

std::unique_ptr<IWriter> create_writer(const std::filesystem::path& output_path) {
    const auto extension = output_path.extension().string();

    if (!factories.contains(extension)) {
        throw ApplicationError{
            ExitCode::output_error,
            "Nepodporovany vystupni format: " + extension
        };
    }

    const auto factory = factories.find(extension);
    const WriterFactory factory_function = factory->second;

    return factory_function();

}