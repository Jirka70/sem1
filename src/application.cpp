#include "application.hpp"
#include "error/applicationError.hpp"
#include "validation/schema/commandLineSchema.hpp"
#include "validation/validation.hpp"
#include "validation/input/commandLineInput.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <charconv>
#include <exitCode.hpp>
#include <command/parse/parseCommand.hpp>
#include <validation/schema/fileSchema.hpp>
#include <read/readLine.hpp>
#include <writer/svgWriter.hpp>
#include <writer/writerFactory.hpp>
#include <validation/schema/outputPathSchema.hpp>

template<typename valueType>
void require_application_validation_t(
    const schema<valueType>& schema,
    const valueType& value,
    exitCode exit_code
) {
    if (const auto error = validate_t(schema, value)) {
        throw ApplicationError{
            exit_code,
            error->field + ": " + error->message
        };
    }
}

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
    require_application_validation_t(commandLineSchema, CommandLineInput{argc, argv}, exitCode::INVALID_ARGUMENTS);

    const CanvasSize image_size = parse_image_size_after_param_validation(argv[3]);
    
    CommandLineArgs args{
        std::filesystem::path(argv[1]),
        std::filesystem::path(argv[2]),
        image_size
    };

    return args;
}

struct LoadCommandResult {
    ::Scene scene;
    std::size_t processed_lines;
};

LoadCommandResult load_commands_to_scene(const std::filesystem::path& input_file) {
    require_application_validation_t(fileSchema, input_file, exitCode::INPUT_ERROR);
    std::ifstream input{input_file};

    if (!input.is_open()) {
        throw ApplicationError{exitCode::INPUT_ERROR,
            "Nelze otevrit vstup: " + input_file.string()};
    }

    std::string line;
    std::size_t line_number{0};
    std::size_t processed_lines{0};

    Scene scene;
    while (read_line(input, line, line_number + 1)) {
        ++line_number;
        const auto tokens = tokenize(line);

        if (tokens.empty()) {
            continue;
        }

        const auto command = parse_command(tokens, line_number);
        command->execute(scene);
        ++processed_lines;
    }

    if (input.bad() || (input.fail() && !input.eof())) {
        throw ApplicationError{
            exitCode::INPUT_ERROR,
            "Chyba pri cteni vstupu: " + input_file.string()
        };
    }

    return {std::move(scene), processed_lines};
}

void write_image(const CommandLineArgs& args, const Scene& scene) {
    require_application_validation_t(outputPathSchema, args.output_path, exitCode::OUTPUT_ERROR);

    std::ofstream output{args.output_path, std::ios::binary};
    if (!output.is_open()) {
        throw ApplicationError{exitCode::OUTPUT_ERROR,
            "Nelze otevrit vystup: " + args.output_path.string()};
    }

    const auto writer = create_writer(args.output_path);
    writer->write(scene, args.size, output);

    output.close();
    if (!output) {
        throw ApplicationError{exitCode::OUTPUT_ERROR,
            "Chyba pri dokonceni vystupu: " + args.output_path.string()};
    }
}

ApplicationResult success(size_t processed_lines) {
    return ApplicationResult{
        .status = applicationStatus::OK,
        .exitCode = exitCode::SUCCESS,
        .processed_lines = processed_lines,
        .error_message = {}
    };
}

ApplicationResult failure(const exitCode exit_code, const std::string& error_message) {
    return ApplicationResult{
        .status = applicationStatus::FAILURE,
        .exitCode = exit_code,
        .processed_lines = 0,
        .error_message = error_message
    };
}

ApplicationResult Application::run(int argc, char* argv[]) {
    try {
        auto parsed_args = parse_args(argc, argv);

        const auto result = load_commands_to_scene(parsed_args.input_path);
        write_image(parsed_args, result.scene);

        return success(result.processed_lines);
    } catch (const ApplicationError& error) {
        return failure(error.code(), error.what());
    } catch (const std::exception& exc) {
        return failure(exitCode::FAILURE, exc.what());
    } catch (...) {
        return failure(exitCode::FAILURE, "Zpracovani se nepodarilo dokoncit kvuli neocekavane chybe.");
    }
}
