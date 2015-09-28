#pragma once

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <ostream>

#include <asciichanges/chords.h>

namespace asciichanges
{
    struct song
    {

    };

    template<typename Iterator>
    struct song_ : qi::grammar<Iterator, song()>
    {
        song_() :
            song_::base_type(start)
        {
            using qi::eps;
            using qi::val;
            using qi::_1;
    
            start =
                eps  [ _val = song() ] >>
                *(
                    chord_
                    |
                    keyvalue_
                    |
                    bars_
                );
        }
    }

    qi::rule<Iterator, song()> start;
}

