#include <util/parse/Number.hpp>


template<typename T> requires (std::same_as<T, int> || std::same_as<T, double>)
std::optional<T> parse_number(std::string_view text) {
    if (text.empty()) {
        return std::nullopt;
    }

    T value{};

    const auto [end, error] = std::from_chars(
        text.data(),
        text.data() + text.size(),
        value
    );

    if (error != std::errc{}
        || end != text.data() + text.size()) {
        return std::nullopt;
    }

    return value;
}

template std::optional<int> parse_number<int>(std::string_view);
template std::optional<double> parse_number<double>(std::string_view);