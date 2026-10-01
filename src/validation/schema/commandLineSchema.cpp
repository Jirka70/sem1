#include "validation/schema/commandLineSchema.hpp"

#include <charconv>
#include <string_view>
#include <system_error>
#include <util/parse/number.hpp>
#include <util/parse/text.hpp>

constexpr int EXPECTED_ARGUMENT_COUNT{4};

bool has_expected_arguments(const CommandLineInput& input) {
    return input.argc == EXPECTED_ARGUMENT_COUNT
        && input.argv != nullptr
        && input.argv[1] != nullptr
        && input.argv[2] != nullptr
        && input.argv[3] != nullptr;
}

bool is_positive_int(std::string_view text) {
    const std::optional<int> maybeNumber = parse_number_t<int>(text);

    if (!maybeNumber.has_value()) return false;
    else return maybeNumber.value() > 0;
}


bool is_valid_size(std::string_view text) {
    constexpr std::string SEPARATOR{"x"};
    constexpr int DIMENSIONS(2);

    std::vector<std::string_view> split_text = split(text, SEPARATOR);


    if (split_text.size() != DIMENSIONS) return false;

    const std::string_view rawWidth = split_text[0];
    const std::string_view rawHeight = split_text[1];

    return is_positive_int(rawWidth)
        && is_positive_int(rawHeight);
}
    

const schema<CommandLineInput> commandLineSchema({
    {
        "arguments",
        "Pouziti: sem1 <vstup> <vystup> <sirka>x<vyska>",
        [](const CommandLineInput& input) {
            return has_expected_arguments(input);
        }
    },
    {
        "input",
        "Cesta ke vstupnimu souboru nesmi byt prazdna",
        [](const CommandLineInput& input) {
            return has_expected_arguments(input)
                && input.argv[1][0] != '\0';
        }
    },
    {
        "output",
        "Cesta k vystupnimu souboru nesmi byt prazdna",
        [](const CommandLineInput& input) {
            return has_expected_arguments(input)
                && input.argv[2][0] != '\0';
        }
    },
    {
        "size",
        "Ocekavany format je napriklad 800x600, rozmery musi byt kladne",
        [](const CommandLineInput& input) {
            return has_expected_arguments(input)
                && is_valid_size(input.argv[3]);
        }
    }
});