#include <memory>
#include "IWriter.hpp"
#include <filesystem>

std::unique_ptr<IWriter> create_writer(const std::filesystem::path& output_path);