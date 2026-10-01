#include <validation/schema/outputPathSchema.hpp>

#include <system_error>

namespace fs = std::filesystem;

const schema<fs::path> outputPathSchema{
    {
        "output",
        "Vystupni cesta musi obsahovat nazev souboru",
        [](const fs::path& path) {
            const auto filename = path.filename();

            return !path.empty()
                && !filename.empty()
                && filename != "."
                && filename != "..";
        }
    },
    {
        "output",
        "Cilova slozka neexistuje nebo k ni nelze pristoupit",
        [](const fs::path& path) {
            const auto parent = path.has_parent_path()
                ? path.parent_path()
                : fs::path{"."};

            std::error_code error;

            return fs::is_directory(parent, error)
                && !error;
        }
    },
    {
        "output",
        "Vystup musi byt novy nebo existujici bezny soubor",
        [](const fs::path& path) {
            std::error_code error;
            const bool exists = fs::exists(path, error);

            if (error) {
                return false;
            }

            if (!exists) {
                return true;
            }

            return fs::is_regular_file(path, error)
                && !error;
        }
    }
};