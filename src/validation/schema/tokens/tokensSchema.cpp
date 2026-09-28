#include <validation/schema/tokens/tokensSchema.hpp>

#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <util/parse/Number.hpp>
#include <span>

const Schema<Tokens> tokensSchema {
    {
        "command",
        "Chybi prikaz",
        [](const Tokens& tokens) {
            return !tokens.empty();
        }
    }
};