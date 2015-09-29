#include <asciichanges/parser.h>
#include <asciichanges/song.h>

namespace asciichanges
{
    parse_info parse(const std::string &s, song &result)
    {
        return parse_info(0, 0, false);
    }

    parse_info parse(std::istream &i, song &result)
    {
        i.unsetf(std::ios::skipws);
        return parse_info(0, 0, false);
    }
}

