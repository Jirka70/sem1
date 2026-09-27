#include "Application.hpp"
#include "error/ApplicationError.hpp"
#include "validation/schema/commandLineSchema.hpp"
#include "validation/Validation.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <charconv>
#include <ExitCode.hpp>
#include <command/parse/parse_command.hpp>
#include <validation/schema/fileSchema.hpp>
#include <read/readLine.hpp>


struct ImageSize {
    int width;
    int height;
};

struct CommandLineArgs {
    std::filesystem::path input_path;
    std::filesystem::path output_path;
    ImageSize size;
};

ImageSize parse_image_size_after_param_validation(std::string_view text) {
    const auto separator = text.find('x');

    const auto width_text = text.substr(0, separator);
    const auto height_text = text.substr(separator + 1);

    ImageSize size{};

    std::from_chars(
        width_text.data(),
        width_text.data() + width_text.size(),
        size.width
    );

    std::from_chars(
        height_text.data(),
        height_text.data() + height_text.size(),
        size.height
    );

    return size;
}

CommandLineArgs parse_args(int argc, char* argv[]) {
    require_validation(commandLineSchema, { argc, argv });

    const ImageSize image_size = parse_image_size_after_param_validation(argv[3]);
    
    CommandLineArgs args{
        std::filesystem::path(argv[1]),
        std::filesystem::path(argv[2]),
        image_size
    };

    return args;
}

void load_commands(const std::filesystem::path& input_file) {
    require_validation(fileSchema, input_file);
    std::ifstream input{input_file};

    if (!input.is_open()) {
        throw ApplicationError{ExitCode::input_error,
            "Nelze otevrit vstup: " + input_file.string()};
    }

    std::string line;
    std::size_t line_number{0};

    Scene scene;
    while (readLine(input, line, line_number + 1)) {
        ++line_number;

        const auto command = parse_command(line, line_number);
        command->execute(scene);

        std::cout << "Line: " << line << std::endl;
    }

    if (input.bad() || (input.fail() && !input.eof())) {
        throw ApplicationError{
            ExitCode::input_error,
            "Chyba pri cteni vstupu: " + input_file.string()
        };
    }
}

void Application::run(int argc, char* argv[]) {
    auto parsed_args = parse_args(argc, argv);
    
    load_commands(parsed_args.input_path);

}