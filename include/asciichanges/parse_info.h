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
        bool partial_success;
        std::string input;

        parse_info(size_t c, size_t t, bool s, std::string i) :
            consumed(c),
            total(t),
            partial_success(s),
            input(i)
        {

        }

        bool successfully_parsed() const
        {
            return partial_success && (consumed == total);
        }
    };

    inline std::ostream &operator<<(std::ostream &o, const parse_info &i)
    {
        o << "successfully_parsed: " << i.successfully_parsed() << " (partial_success: " << i.partial_success << " consumed: " << i.consumed << " / total: " << i.total << ")";

        return o;
    }
}

