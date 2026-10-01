#include <util/parse/number.hpp>


template<typename valueType> requires (std::same_as<valueType, int> || std::same_as<valueType, double>)
std::optional<valueType> parse_number_t(std::string_view text) {
    if (text.empty()) {
        return std::nullopt;
    }

    valueType value{};

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

template std::optional<int> parse_number_t<int>(std::string_view);
template std::optional<double> parse_number_t<double>(std::string_view);