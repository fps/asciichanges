#pragma once

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <ostream>

#include <asciichanges/chords.h>
#include <asciichanges/results.h>

#include <string>

namespace asciichanges
{
    using qi::eps;
    using qi::_val;
    using qi::_1;
    using qi::blank;
    using qi::eol;
    using qi::alnum;
    using qi::lit;

    template<typename Iterator>
    struct keyvalue_ : qi::grammar<Iterator, keyvalue()>
    {
        keyvalue_() :
            keyvalue_::base_type(start)
        {
            start = 
                qi::eps [ _val = keyvalue() ] >>
                (+alnum >> ":" >> *blank >> +(alnum | "/"));
        }

        qi::rule<Iterator, keyvalue()> start;
    };
        
    template<typename Iterator>
    struct bars_ : qi::grammar<Iterator, bars()>
    {
        chord_<Iterator> chord;

        bars_() : 
            bars_::base_type(start)
        {

            start = 
                eps [ _val = bars() ] >>
                +("|" >> -lit(":") >> *blank >> *(chord >> *blank) >> -lit(":")) >> "|"
            ;
        }

        qi::rule<Iterator, bars()> start;
    };


    template<typename Iterator>
    struct song_ : qi::grammar<Iterator, song()>
    {
        chord_<Iterator> chord;
        keyvalue_<Iterator> keyvalue;
        bars_<Iterator> bars;

        song_() :
            song_::base_type(start)
        {
            endofline =
                ";"
                |
                eol
            ;

            comment =     
                "--" >> *(alnum | blank)
            ;

            line = 
                comment
                |
                (*blank >> keyvalue >> *blank)
                |
                (*blank >> bars >> *blank)
                |
                (*blank >> chord >> *blank)
                |
                *blank
            ;

            start =
                eps  [ _val = song() ] >>
                (line % endofline) >> -endofline
            ;
        }

        qi::rule<Iterator, song()> start;
        qi::rule<Iterator> comment;
        qi::rule<Iterator> endofline;
        qi::rule<Iterator> line;
    };
}

