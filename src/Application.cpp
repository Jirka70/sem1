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
#include <writer/SVGWriter.hpp>


struct CommandLineArgs {
    std::filesystem::path input_path;
    std::filesystem::path output_path;
    CanvasSize size;
};

CanvasSize parse_image_size_after_param_validation(std::string_view text) {
    const auto separator = text.find('x');

    const auto width_text = text.substr(0, separator);
    const auto height_text = text.substr(separator + 1);

    CanvasSize size{};

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

    const CanvasSize image_size = parse_image_size_after_param_validation(argv[3]);
    
    CommandLineArgs args{
        std::filesystem::path(argv[1]),
        std::filesystem::path(argv[2]),
        image_size
    };

    return args;
}

Scene load_commands(const std::filesystem::path& input_file) {
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

    return scene;
}

void Application::run(int argc, char* argv[]) {
    auto parsed_args = parse_args(argc, argv);
    
    if (parsed_args.output_path.extension() != ".svg") {
        throw ApplicationError{ExitCode::output_error,
            "Podporovany vystupni format je .svg"};
    }

    const Scene scene = load_commands(parsed_args.input_path);
    std::ofstream output{parsed_args.output_path, std::ios::binary};
    if (!output.is_open()) {
        throw ApplicationError{ExitCode::output_error,
            "Nelze otevrit vystup: " + parsed_args.output_path.string()};
    }

    SVGWriter writer;
    writer.write(scene, parsed_args.size, output);

    output.close();
    if (!output) {
        throw ApplicationError{ExitCode::output_error,
            "Chyba pri dokonceni vystupu: " + parsed_args.output_path.string()};
    }

}
