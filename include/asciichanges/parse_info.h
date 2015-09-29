#pragma once

#include <string>
#include <ostream>

namespace asciichanges
{
    /**
        A successful parse will have consume == total and success == true.
    */
    struct parse_info
    {
        size_t consumed;
        size_t total;
        bool success;
        std::string input;

        parse_info(size_t c, size_t t, bool s, std::string i) :
            consumed(c),
            total(t),
            success(s),
            input(i)
        {

        }
    };

    inline std::ostream &operator<<(std::ostream &o, const parse_info &i)
    {
        o << "success: " << i.success << " consumed: " << i.consumed << " / total: " << i.total;

        return o;
    }
}

