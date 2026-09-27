#include <command/parse/parse_command.hpp>
#include <unordered_map>
#include <validation/Validation.hpp>
#include <util/parse/Text.hpp>
#include <util/parse/Number.hpp>
#include <error/ApplicationError.hpp>
#include <span>
#include <validation/schema/shape/circleSchema.hpp>
#include <validation/schema/tokens/circleTokensSchema.hpp>
#include <validation/schema/tokens/lineTokensSchema.hpp>
#include <validation/schema/tokens/rectangleTokensSchema.hpp>
#include <validation/schema/tokens/tokensSchema.hpp>
#include <validation/schema/shape/lineSchema.hpp>
#include <validation/schema/shape/rectangleSchema.hpp>
#include <command/DrawLineCommand.hpp>
#include <command/DrawCircleCommand.hpp>
#include <command/DrawRectangleCommand.hpp>


constexpr size_t PARAM_START_INDEX = 1;

std::unique_ptr<DrawCircleCommand> parse_circle_command(const Tokens& validated_tokens) {
    require_validation(circleTokensSchema, validated_tokens);

    const auto& circle_parameters = std::span<const std::string_view>{validated_tokens}
        .subspan(PARAM_START_INDEX);

    const Circle circle{
        .center = {
            .x = parse_number<double>(circle_parameters[0]).value(),
            .y = parse_number<double>(circle_parameters[1]).value()
        },
        .radius = parse_number<double>(circle_parameters[2]).value()
    };

    require_validation(circleSchema, circle);

    return std::make_unique<DrawCircleCommand>(circle);
}

std::unique_ptr<DrawLineCommand> parse_line_command(const Tokens& validated_tokens) {
    require_validation(lineTokensSchema, validated_tokens);

    const auto parameters = std::span<const std::string_view>{validated_tokens}
        .subspan(PARAM_START_INDEX);

    const Line line{
        .start = {
            .x = parse_number<double>(parameters[0]).value(),
            .y = parse_number<double>(parameters[1]).value()
        },
        .end = {
            .x = parse_number<double>(parameters[2]).value(),
            .y = parse_number<double>(parameters[3]).value()
        }
    };

    require_validation(lineSchema, line);

    return std::make_unique<DrawLineCommand>(line);
}

std::unique_ptr<DrawRectangleCommand> parse_rectangle_command(const Tokens& validated_tokens) {
    require_validation(rectangleTokensSchema, validated_tokens);

    const auto parameters = std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const double left = parse_number<int>(parameters[0]).value();
    const double top = parse_number<int>(parameters[1]).value();
    const double width = parse_number<double>(parameters[2]).value();
    const double height = parse_number<double>(parameters[3]).value();
    const double right = left + width;
    const double bottom = top + height;

    const Rectangle rectangle{
        .corners = {
            Point{.x = left, .y = top},
            Point{.x = right, .y = top},
            Point{.x = right, .y = bottom},
            Point{.x = left, .y = bottom}
        }
    };

    require_validation(rectangleSchema, rectangle);

    return std::make_unique<DrawRectangleCommand>(rectangle);
}

static const std::unordered_map<std::string_view, CommandFactory> factories{
    {"circle", parse_circle_command},
    {"line", parse_line_command},
    {"rect", parse_rectangle_command}
};

std::unique_ptr<ICommand> parse_command(std::string_view line, size_t line_number) {
    Tokens tokens = tokenize(line);
    try {
        require_validation(tokensSchema, tokens);

        const std::string_view& commant_type = tokens.front();
        if (!factories.contains(commant_type)) {
            std::cout << "Neznamy prikaz " << commant_type << std::endl;
            return nullptr;
        }

        const auto factory = factories.find(commant_type);
        const auto factory_function = factory->second;

        return factory_function(tokens);

    } catch (const std::invalid_argument& error) {
        throw ApplicationError{ExitCode::input_error, "Radek " + std::to_string(line_number) + ": " + error.what()};
    }
}
