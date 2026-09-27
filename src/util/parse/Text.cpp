#include <util/parse/Text.hpp>
#include <command/parse/parse_command.hpp>

std::vector<std::string_view> split(std::string_view text, std::string_view separator) {
    if (separator.empty()) {
        throw std::invalid_argument{"Oddelovac nesmi byt prazdny"};
    }

    std::vector<std::string_view> parts;

    while (true) {
        const auto position = text.find(separator);

        if (position == std::string_view::npos) {
            parts.push_back(text);
            return parts;
        }

        parts.push_back(text.substr(0, position));
        text.remove_prefix(position + separator.size());
    }
}
Tokens tokenize(std::string_view text) {
    constexpr std::string SEPARATOR{" "};

    Tokens tokens;

    const std::vector<std::string_view> parts = split(text, SEPARATOR);
    for (const std::string_view part : parts) {
        if (!part.empty()) {
            tokens.push_back(part);
        }
    }

    return tokens;
}