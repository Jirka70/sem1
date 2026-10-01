#ifndef SEM1_UTIL_PARSE_NUMBER_HPP
#define SEM1_UTIL_PARSE_NUMBER_HPP

#include <iostream>
#include <charconv>
#include <concepts>
#include <optional>
#include <string_view>


template<typename valueType> 
requires (std::same_as<valueType, int> || std::same_as<valueType, double> || std::same_as<valueType, float>)
std::optional<valueType> parse_number_t(std::string_view text);

#endif
