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

bool is_whitespace(char character) {
    return std::isspace(static_cast<unsigned char>(character)) != 0;
}

std::string_view trim(std::string_view text) {
    while (!text.empty() && is_whitespace(text.front())) {
        text.remove_prefix(1);
    }

    while (!text.empty() && is_whitespace(text.back())) {
        text.remove_suffix(1);
    }

    return text;
}

std::string_view remove_comment(std::string_view text) noexcept
{
    constexpr char COMMENT_START_CHAR{'#'};
    return text.substr(0, text.find(COMMENT_START_CHAR));
}

Tokens tokenize(std::string_view text) {
    Tokens tokens;

    text = remove_comment(text);
    while (!text.empty()) {
        while (!text.empty() && is_whitespace(text.front())) {
            text.remove_prefix(1);
        }

        if (text.empty()) {
            break;
        }

        std::size_t length = 0;

        while (length < text.size()
               && !is_whitespace(text[length])) {
            ++length;
        }

        tokens.push_back(text.substr(0, length));
        text.remove_prefix(length);
    }

    return tokens;
}