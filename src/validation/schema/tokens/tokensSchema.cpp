#include <validation/schema/tokens/tokensSchema.hpp>

#include <algorithm>
#include <charconv>
#include <cmath>
#include <cstddef>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <util/parse/number.hpp>
#include <span>

const schema<tokens> tokensSchema {
    {
        "command",
        "Chybi prikaz",
        [](const tokens& tokens) {
            return !tokens.empty();
        }
    }
};