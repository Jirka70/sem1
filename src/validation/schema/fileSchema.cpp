#include <validation/schema/fileSchema.hpp>

constexpr size_t MAX_SIZE_B{100'000'000};

const schema<std::filesystem::path> fileSchema{
    {
        "input",
        "Vstup musi byt bezny soubor",
        [](const std::filesystem::path& path) {
            std::error_code error;
            return std::filesystem::is_regular_file(path, error)
                && !error;
        }
    },
    {
        "input",
        "Soubor neexistuje nebo k nemu nelze pristoupit",
        [](const std::filesystem::path& path) {
            std::error_code error;
            const bool exists = std::filesystem::exists(path, error);

            return !error && exists;
        }
    },
    {
        "input",
        "Velikost souboru nesmi presahnout 100 MB",
        [](const std::filesystem::path& path) {
            std::error_code error;
            const size_t size = std::filesystem::file_size(path, error);

            return !error && size <= MAX_SIZE_B;
        }
    }
};