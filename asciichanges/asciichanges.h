#pragma once

#include <boost/spirit/include/qi.hpp>

namespace asciichanges
{
    namespace qi = boost::spirit::qi;

    struct abcdefg_ : qi::symbols<char, unsigned>
    {
        abcdefg_()
        {
            add
                ("C", 60)
                ("D", 62)
                ("E", 64)
                ("F", 65)
                ("G", 67)
                ("A", 69)
                ("B", 71)
            ;
        }
    } abcdefg;

    struct sharp_ : qi::symbols<char, int>
    {
        sharp_()
        {
            add
                ("#", 1)
            ;
        }
    } sharp;

    struct flat_ : qi::symbols<char, int>
    {
        flat_()
        {
            add
                ("b", -1)
            ;
        }
    } flat;

    template<typename Iterator>
    struct accidentals_ : qi::grammar<Iterator>
    {
        accidentals_() : 
            accidentals_::base_type(start)
        {
            start =  +flat | +sharp;
        }

        qi::rule<Iterator> start;
    };

    template<typename Iterator>
    struct note_ : qi::grammar<Iterator>
    {
        accidentals_<Iterator> accidentals;

        note_() : 
            note_::base_type(start)
        {
            start = abcdefg >> -accidentals;
        }

        qi::rule<Iterator> start;
    };
}

