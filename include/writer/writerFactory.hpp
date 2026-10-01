#include <memory>
#include "iWriter.hpp"
#include <filesystem>

std::unique_ptr<iWriter> create_writer(const std::filesystem::path& output_path);