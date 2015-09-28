#pragma once

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <ostream>

#include <asciichanges/chords.h>
#include <string>

namespace asciichanges
{
    struct event
    {
        virtual ~event() 
        { 

        }
    };

    struct keyvalue
    {
        std::string key;
        std::string value;

        keyvalue(const std::string k = "", const std::string v = "") :
            key(k),
            value(v)
        {

        }
    };

    struct bars
    {

    };

    struct song
    {

    };

    std::ostream &operator<<(std::ostream &o, const song &s)
    {
        o << "song";
        return o;
    }

    template<typename Iterator>
    struct comment_ : qi::grammar<Iterator>
    {
        comment_() :
            comment_::base_type(start)
        {
            using qi::eps;
            using qi::_val;
            using qi::_1;
            using qi::alnum;
 
            start = 
                "--" >> *alnum >> "\n";
        }

        qi::rule<Iterator> start;
    };
 
    template<typename Iterator>
    struct keyvalue_ : qi::grammar<Iterator, keyvalue()>
    {
        keyvalue_() :
            keyvalue_::base_type(start)
        {
            using qi::eps;
            using qi::_val;
            using qi::_1;
            using qi::alnum;
 
            start = 
                qi::eps [ _val = keyvalue() ] >>
                (+alnum >> ':' >> +alnum);
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
            using qi::eps;
            using qi::_val;
            using qi::_1;

            start = 
                eps [ _val = bars() ] >>
                "|" >> *(chord) >> "|"
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
        comment_<Iterator> comment;

        song_() :
            song_::base_type(start)
        {
            using qi::eps;
            using qi::_val;
            using qi::_1;
    
            start =
                eps  [ _val = song() ] >>
                +(
                    "\n"
                    |
                    comment
                    |
                    chord
                    |
                    keyvalue
                    |
                    bars
                );
        }

        qi::rule<Iterator, song()> start;
    };
}

