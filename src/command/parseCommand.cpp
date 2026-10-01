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

std::unique_ptr<drawCircleCommand> parse_circle_command(const tokens& validated_tokens) {
    require_validation_t(circleTokensSchema, validated_tokens);

    const auto& circle_parameters = std::span<const std::string_view>{validated_tokens}
        .subspan(PARAM_START_INDEX);

    const circleArgs args = circleArgs{
        .center = {
            .x = parse_number_t<double>(circle_parameters[0]).value(),
            .y = parse_number_t<double>(circle_parameters[1]).value()
        },
        .radius = parse_number_t<double>(circle_parameters[2]).value()
    };

    const circle circle{args};

    return std::make_unique<drawCircleCommand>(circle);
}

std::unique_ptr<drawLineCommand> parse_line_command(const tokens& validated_tokens) {
    require_validation_t(lineTokensSchema, validated_tokens);

    const auto parameters = std::span<const std::string_view>{validated_tokens}
        .subspan(PARAM_START_INDEX);

    
    const lineArgs args = lineArgs{
        .start = {
            .x = parse_number_t<double>(parameters[0]).value(),
            .y = parse_number_t<double>(parameters[1]).value()
        },
        .end = {
            .x = parse_number_t<double>(parameters[2]).value(),
            .y = parse_number_t<double>(parameters[3]).value()
        }
    };

    const line line{args};    
    return std::make_unique<drawLineCommand>(line);
}

std::unique_ptr<drawRectangleCommand> parse_rectangle_command(const tokens& validated_tokens) {
    require_validation_t(rectangleTokensSchema, validated_tokens);

    const auto parameters = std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const double left = parse_number_t<int>(parameters[0]).value();
    const double top = parse_number_t<int>(parameters[1]).value();
    const double width = parse_number_t<double>(parameters[2]).value();
    const double height = parse_number_t<double>(parameters[3]).value();
    const double right = left + width;
    const double bottom = top + height;

    const rectangleArgs args = rectangleArgs{
        .corners = {
            vector2D{.x = left, .y = top},
            vector2D{.x = right, .y = top},
            vector2D{.x = right, .y = bottom},
            vector2D{.x = left, .y = bottom}
        }
    };

    const rectangle rectangle{args};

    return std::make_unique<drawRectangleCommand>(rectangle);
}

std::unique_ptr<translateCommand> parse_translate_command(const tokens& validated_tokens) {
    require_validation_t(translateTokensSchema, validated_tokens);

    const auto parameters =
        std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const vector2D args = vector2D{
        .x = static_cast<double>(
            parse_number_t<int>(parameters[0]).value()
        ),
        .y = static_cast<double>(
            parse_number_t<int>(parameters[1]).value()
        )
    };

    return std::make_unique<translateCommand>(args);
}

std::unique_ptr<rotateCommand> parse_rotate_command(const tokens& validated_tokens) {
    require_validation_t(rotateTokensSchema, validated_tokens);

    const auto parameters =
        std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const rotationArgs args = rotationArgs{
        .center = {
            .x = static_cast<double>(
                parse_number_t<int>(parameters[0]).value()
            ),
            .y = static_cast<double>(
                parse_number_t<int>(parameters[1]).value()
            )
        },
        .angleDegrees = parse_number_t<double>(parameters[2]).value()
    };

    return std::make_unique<rotateCommand>(args);
}

std::unique_ptr<scaleCommand> parse_scale_command(const tokens& validated_tokens) {
    require_validation_t(scaleTokensSchema, validated_tokens);

    const auto parameters =
        std::span<const std::string_view>{validated_tokens}
            .subspan(PARAM_START_INDEX);

    const scaleArgs args = scaleArgs{
        .center = {
            .x = static_cast<double>(
                parse_number_t<int>(parameters[0]).value()
            ),
            .y = static_cast<double>(
                parse_number_t<int>(parameters[1]).value()
            )
        },
        .factor = parse_number_t<double>(parameters[2]).value()
    };

    return std::make_unique<scaleCommand>(args);
}

static const std::unordered_map<std::string_view, commandFactory>factories{
    {"circle", parse_circle_command},
    {"line", parse_line_command},
    {"rect", parse_rectangle_command},
    {"translate", parse_translate_command},
    {"rotate", parse_rotate_command},
    {"scale", parse_scale_command}
};


std::unique_ptr<iCommand> parse_command(const tokens& tokens, size_t line_number) {
    try {
        const std::string_view& commant_type = tokens.front();
        if (!factories.contains(commant_type)) {
            throw std::invalid_argument{"Neznamy prikaz: " + std::string{tokens.front()}};
        }

        const auto factory = factories.find(commant_type);
        const auto factory_function = factory->second;

        return factory_function(tokens);

    } catch (const std::invalid_argument& error) {
        throw applicationError{exitCode::INPUT_ERROR, "Radek " + std::to_string(line_number) + ": " + error.what()};
    }
}
