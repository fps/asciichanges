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

    template<typename Iterator>
    struct minor_ : qi::grammar<Iterator>
    {
        minor_() : 
            minor_::base_type(start)
        {
            start = qi::string("minor") | qi::string("min") | qi::string("m");
        }

        qi::rule<Iterator> start;
    };

    template<typename Iterator>
    struct suspended_ : qi::grammar<Iterator>
    {
        suspended_() : 
            suspended_::base_type(start)
        {
            start = qi::string("sus4") | qi::string("sus2") | qi::string("sus");
        }

        qi::rule<Iterator> start;
    };

    template<typename Iterator>
    struct extensions_ : qi::grammar<Iterator>
    {
        extensions_() : 
            extensions_::base_type(start)
        {
            extensions = qi::string("b5") | qi::string("6") | qi::string("7") | qi::string("maj7") | qi::string("b9") | qi::string("9") | qi::string("#9") | qi::string("#11") | qi::string("11") | qi::string("b13") | qi::string("13");
            //start = +(qi::string("b5") | qi::string("6") | qi::string("7") | qi::string("maj7"));
		
			comma_separated = extensions >> *(-qi::string(",") >> extensions);
			bracketed = qi::string("(") >> comma_separated >> qi::string(")");
			start = (comma_separated >> -bracketed) | bracketed;
        }

        qi::rule<Iterator> start;
		qi::rule<Iterator> extensions;
		qi::rule<Iterator> bracketed;
		qi::rule<Iterator> comma_separated;
    };


    template<typename Iterator>
    struct chord_ : qi::grammar<Iterator>
    {

        note_<Iterator> note;
        minor_<Iterator> minor;
        suspended_<Iterator> suspended;
        extensions_<Iterator> extensions;

        chord_() : 
            chord_::base_type(start)
        {
            start =  note >> -(extensions | ((minor | suspended) >> -extensions)) >> -('/' >> note);
        }

        qi::rule<Iterator> start;
    };

   
}

