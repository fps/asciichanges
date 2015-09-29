#pragma once

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

        parse_info(size_t c, size_t t, bool s) :
            consumed(c),
            total(t),
            success(s)
        {

        }
    };
}

