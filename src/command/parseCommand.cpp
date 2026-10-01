#include <command/parse/parseCommand.hpp>
#include <unordered_map>
#include <validation/validation.hpp>
#include <util/parse/text.hpp>
#include <util/parse/number.hpp>
#include <error/applicationError.hpp>
#include <span>
#include <validation/schema/tokens/circleTokensSchema.hpp>
#include <validation/schema/tokens/lineTokensSchema.hpp>
#include <validation/schema/tokens/rectangleTokensSchema.hpp>
#include <validation/schema/tokens/tokensSchema.hpp>
#include <validation/schema/geometrySchemas.hpp>
#include <command/drawCircleCommand.hpp>
#include <command/drawLineCommand.hpp>
#include <command/drawRectangleCommand.hpp>
#include <command/translateCommand.hpp>
#include <validation/schema/tokens/translateTokensSchema.hpp>
#include <command/rotateCommand.hpp>
#include <validation/schema/tokens/rotateTokensSchema.hpp>
#include <command/scaleCommand.hpp>
#include <validation/schema/tokens/scaleTokensSchema.hpp>


constexpr size_t PARAM_START_INDEX = 1;

std::unique_ptr<DrawCircleCommand> parse_circle_command(const tokens& validated_tokens) {
    require_validation_t(circleTokensSchema, validated_tokens);

    const auto& validated_circle_parameters = std::span<const std::string_view>{validated_tokens}
        .subspan(PARAM_START_INDEX);

    const CircleArgs args = CircleArgs{
        .center = {
            .x = parse_number_t<double>(validated_circle_parameters[0]).value(),
            .y = parse_number_t<double>(validated_circle_parameters[1]).value()
        },
        .radius = parse_number_t<double>(validated_circle_parameters[2]).value()
    };

    const Circle circle{args};

    return std::make_unique<DrawCircleCommand>(circle);
}

std::unique_ptr<DrawLineCommand> parse_line_command(const tokens& validated_tokens) {
    require_validation_t(lineTokensSchema, validated_tokens);

    const auto validated_parameters = std::span<const std::string_view>{validated_tokens}
        .subspan(PARAM_START_INDEX);

    
    const LineArgs args = LineArgs{
        .start = {
            .x = parse_number_t<double>(validated_parameters[0]).value(),
            .y = parse_number_t<double>(validated_parameters[1]).value()
        },
        .end = {
            .x = parse_number_t<double>(validated_parameters[2]).value(),
            .y = parse_number_t<double>(validated_parameters[3]).value()
        }
    };

    const Line line{args};    
    return std::make_unique<DrawLineCommand>(line);
}

std::unique_ptr<DrawRectangleCommand> parse_rectangle_command(const tokens& validated_tokens) {
    require_validation_t(rectangleTokensSchema, validated_tokens);

    const auto validated_parameters = std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const double left = parse_number_t<int>(validated_parameters[0]).value();
    const double top = parse_number_t<int>(validated_parameters[1]).value();
    const double width = parse_number_t<double>(validated_parameters[2]).value();
    const double height = parse_number_t<double>(validated_parameters[3]).value();
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

std::unique_ptr<TranslateCommand> parse_translate_command(const tokens& validated_tokens) {
    require_validation_t(translateTokensSchema, validated_tokens);

    const auto validated_parameters = std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const Vector2D args = Vector2D{
        .x = static_cast<double>(
            parse_number_t<int>(validated_parameters[0]).value()
        ),
        .y = static_cast<double>(
            parse_number_t<int>(validated_parameters[1]).value()
        )
    };

    return std::make_unique<TranslateCommand>(args);
}

std::unique_ptr<RotateCommand> parse_rotate_command(const tokens& validated_tokens) {
    require_validation_t(rotateTokensSchema, validated_tokens);

    const auto validated_parameters =
        std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const RotationArgs args = RotationArgs{
        .center = {
            .x = static_cast<double>(
                parse_number_t<int>(validated_parameters[0]).value()
            ),
            .y = static_cast<double>(
                parse_number_t<int>(validated_parameters[1]).value()
            )
        },
        .angleDegrees = parse_number_t<double>(validated_parameters[2]).value()
    };

    return std::make_unique<RotateCommand>(args);
}

std::unique_ptr<ScaleCommand> parse_scale_command(const tokens& validated_tokens) {
    require_validation_t(scaleTokensSchema, validated_tokens);

    const auto validated_parameters =
        std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const ScaleArgs args = ScaleArgs{
        .center = {
            .x = static_cast<double>(
                parse_number_t<int>(validated_parameters[0]).value()
            ),
            .y = static_cast<double>(
                parse_number_t<int>(validated_parameters[1]).value()
            )
        },
        .factor = parse_number_t<double>(validated_parameters[2]).value()
    };

    return std::make_unique<ScaleCommand>(args);
}

static const std::unordered_map<std::string_view, commandFactory>factories{
    {"circle", parse_circle_command},
    {"line", parse_line_command},
    {"rect", parse_rectangle_command},
    {"translate", parse_translate_command},
    {"rotate", parse_rotate_command},
    {"scale", parse_scale_command}
};


std::unique_ptr<ICommand> parse_command(const tokens& tokens, size_t line_number) {
    try {
        const std::string_view& commant_type = tokens.front();
        if (!factories.contains(commant_type)) {
            throw std::invalid_argument{"Neznamy prikaz: " + std::string{tokens.front()}};
        }

        const auto factory = factories.find(commant_type);
        const auto factory_function = factory->second;

        return factory_function(tokens);

    } catch (const std::invalid_argument& error) {
        throw ApplicationError{exitCode::INPUT_ERROR, "Radek " + std::to_string(line_number) + ": " + error.what()};
    }
}
