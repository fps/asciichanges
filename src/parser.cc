#include <asciichanges/parser.h>
#include <asciichanges/song.h>

#include <string>

namespace asciichanges
{
    parse_info parse(const std::string &s, song &result)
    {
        
        return parse_info(0, 0, false);
    }

    parse_info parse(std::istream &i, song &result)
    {
        i.unsetf(std::ios::skipws);

        std::string input;
        std::string line;
        while (std::getline(i, line))
        {
            input += line + "\n";
        }

        typedef std::string::const_iterator iterator;
        iterator begin = input.begin();
        iterator iter = begin;
        iterator end = input.end();

        asciichanges::song_<iterator> parser;

        bool r = boost::spirit::qi::parse(iter, end, parser, result);
        return parse_info(iter - begin, end - begin, r);
    }
}

