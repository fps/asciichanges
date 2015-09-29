#pragma once

#include <asciichanges/results.h>

#include <iostream>
#include <istream>

namespace asciichanges
{
    struct parse_info
    {
        size_t consumed;
        size_t total;
        bool success;

        parse_info(size_t c, size_t t, bool s) :
            consumed(c),
            total(t),
            success(s)
        {

        }
    };

    inline std::ostream &operator<<(std::ostream &o, const parse_info &i)
    {
        o << "success: " << i.success << " consumed: " << i.consumed << " / total: " << i.total;
        return o;
    }

    parse_info parse(const std::string &s, song &result);

    parse_info parse(std::istream &i, song &result);
}

