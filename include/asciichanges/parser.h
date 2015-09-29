#pragma once

#include <asciichanges/results.h>
#include <asciichanges/parse_info.h>

#include <iostream>
#include <istream>

namespace asciichanges
{
    inline std::ostream &operator<<(std::ostream &o, const parse_info &i)
    {
        o << "success: " << i.success << " consumed: " << i.consumed << " / total: " << i.total;
        return o;
    }

    parse_info parse(const std::string &s, song &result);

    parse_info parse(std::istream &i, song &result);
}

