#include <asciichanges/parser.h>
#include <asciichanges/song.h>

#include <string>

namespace asciichanges
{
    parse_info parse(const std::string &s, results::song &result)
    {
        typedef std::string::const_iterator iterator;
        iterator begin = s.begin();
        iterator iter = begin;
        iterator end = s.end();

        asciichanges::song_<iterator> parser;

        bool r = boost::spirit::qi::parse(iter, end, parser, result);
        return parse_info(iter - begin, end - begin, r, s);
    }

    parse_info parse(std::istream &i, results::song &result)
    {
        i.unsetf(std::ios::skipws);

        std::string input;
        std::string line;
        while (std::getline(i, line))
        {
            input += line + "\n";
        }

        return parse(input, result);
    }
}

