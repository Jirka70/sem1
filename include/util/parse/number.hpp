#ifndef PARSE_NUMBER_HPP
#define PARSE_NUMBER_HPP

#include <iostream>
#include <charconv>
#include <concepts>
#include <optional>
#include <string_view>


template<typename T> 
requires (std::same_as<T, int> || std::same_as<T, double> || std::same_as<T, float>)
std::optional<T> parse_number(std::string_view text);

#endif
