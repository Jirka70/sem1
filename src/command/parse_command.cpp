#include <command/parse/parse_command.hpp>
#include <unordered_map>
#include <validation/Validation.hpp>
#include <util/parse/Text.hpp>
#include <util/parse/Number.hpp>
#include <error/ApplicationError.hpp>
#include <span>
#include <validation/schema/tokens/circleTokensSchema.hpp>
#include <validation/schema/tokens/lineTokensSchema.hpp>
#include <validation/schema/tokens/rectangleTokensSchema.hpp>
#include <validation/schema/tokens/tokensSchema.hpp>
#include <validation/schema/geometrySchemas.hpp>
#include <command/DrawCircleCommand.hpp>
#include <command/DrawLineCommand.hpp>
#include <command/DrawRectangleCommand.hpp>
#include <command/TranslateCommand.hpp>
#include <validation/schema/tokens/translateTokensSchema.hpp>
#include <command/RotateCommand.hpp>
#include <validation/schema/tokens/rotateTokensSchema.hpp>
#include <command/ScaleCommand.hpp>
#include <validation/schema/tokens/scaleTokensSchema.hpp>


constexpr size_t PARAM_START_INDEX = 1;

std::unique_ptr<DrawCircleCommand> parse_circle_command(const Tokens& validated_tokens) {
    require_validation(circleTokensSchema, validated_tokens);

    const auto& circle_parameters = std::span<const std::string_view>{validated_tokens}
        .subspan(PARAM_START_INDEX);

    const CircleArgs args = CircleArgs{
        .center = {
            .x = parse_number<double>(circle_parameters[0]).value(),
            .y = parse_number<double>(circle_parameters[1]).value()
        },
        .radius = parse_number<double>(circle_parameters[2]).value()
    };

    const Circle circle{args};

    return std::make_unique<DrawCircleCommand>(circle);
}

std::unique_ptr<DrawLineCommand> parse_line_command(const Tokens& validated_tokens) {
    require_validation(lineTokensSchema, validated_tokens);

    const auto parameters = std::span<const std::string_view>{validated_tokens}
        .subspan(PARAM_START_INDEX);

    
    const LineArgs args = LineArgs{
        .start = {
            .x = parse_number<double>(parameters[0]).value(),
            .y = parse_number<double>(parameters[1]).value()
        },
        .end = {
            .x = parse_number<double>(parameters[2]).value(),
            .y = parse_number<double>(parameters[3]).value()
        }
    };

    const Line line{args};    
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

    const RectangleArgs args = RectangleArgs{
        .corners = {
            Vector2D{.x = left, .y = top},
            Vector2D{.x = right, .y = top},
            Vector2D{.x = right, .y = bottom},
            Vector2D{.x = left, .y = bottom}
        }
    };

    const Rectangle rectangle{args};

    return std::make_unique<DrawRectangleCommand>(rectangle);
}

std::unique_ptr<TranslateCommand> parse_translate_command(const Tokens& validated_tokens) {
    require_validation(translateTokensSchema, validated_tokens);

    const auto parameters =
        std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const Vector2D args = Vector2D{
        .x = static_cast<double>(
            parse_number<int>(parameters[0]).value()
        ),
        .y = static_cast<double>(
            parse_number<int>(parameters[1]).value()
        )
    };

    return std::make_unique<TranslateCommand>(args);
}

std::unique_ptr<RotateCommand> parse_rotate_command(const Tokens& validated_tokens) {
    require_validation(rotateTokensSchema, validated_tokens);

    const auto parameters =
        std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const RotationArgs args = RotationArgs{
        .center = {
            .x = static_cast<double>(
                parse_number<int>(parameters[0]).value()
            ),
            .y = static_cast<double>(
                parse_number<int>(parameters[1]).value()
            )
        },
        .angleDegrees = parse_number<double>(parameters[2]).value()
    };

    return std::make_unique<RotateCommand>(args);
}

std::unique_ptr<ScaleCommand> parse_scale_command(const Tokens& validated_tokens) {
    require_validation(scaleTokensSchema, validated_tokens);

    const auto parameters =
        std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const ScaleArgs args = ScaleArgs{
        .center = {
            .x = static_cast<double>(
                parse_number<int>(parameters[0]).value()
            ),
            .y = static_cast<double>(
                parse_number<int>(parameters[1]).value()
            )
        },
        .factor = parse_number<double>(parameters[2]).value()
    };

    return std::make_unique<ScaleCommand>(args);
}

static const std::unordered_map<std::string_view, CommandFactory>factories{
    {"circle", parse_circle_command},
    {"line", parse_line_command},
    {"rect", parse_rectangle_command},
    {"translate", parse_translate_command},
    {"rotate", parse_rotate_command},
    {"scale", parse_scale_command}
};


std::unique_ptr<ICommand> parse_command(std::string_view line, size_t line_number) {
    Tokens tokens = tokenize(line);
    try {
        require_validation(tokensSchema, tokens);

        const std::string_view& commant_type = tokens.front();
        if (!factories.contains(commant_type)) {
            throw std::invalid_argument{"Neznamy prikaz: " + std::string{tokens.front()}};
        }

        const auto factory = factories.find(commant_type);
        const auto factory_function = factory->second;

        return factory_function(tokens);

    } catch (const std::invalid_argument& error) {
        throw ApplicationError{ExitCode::input_error, "Radek " + std::to_string(line_number) + ": " + error.what()};
    }
}
