#pragma once

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include <asciichanges/results.h>

#include <ostream>

namespace asciichanges
{
    namespace qi = boost::spirit::qi;
    namespace phoenix = boost::phoenix;

    using qi::eps;
    using qi::_val;
    using qi::_1;

    struct abcdefg_ : qi::symbols<char, results::note::name>
    {
        abcdefg_()
        {
            add
                ("C", results::note::name::C)
                ("D", results::note::name::D)
                ("E", results::note::name::E)
                ("F", results::note::name::F)
                ("G", results::note::name::G)
                ("A", results::note::name::A)
                ("B", results::note::name::B)
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
    struct accidentals_ : qi::grammar<Iterator, int()>
    {
        accidentals_() : 
            accidentals_::base_type(start)
        {
            start = 
                qi::eps [_val = 0] >>
                (
                          +flat  [_val += _1]
                        | +sharp [_val += _1]
                )
            ;
        }

        qi::rule<Iterator, int()> start;
    };

    template<typename Iterator>
    struct note_ : qi::grammar<Iterator, results::note()>
    {
        accidentals_<Iterator> accidentals;

        note_() : 
            note_::base_type(start)
        {
            start = 
                eps [_val = results::note()] >>
                abcdefg      [phoenix::bind(&results::note::m_name, qi::_val) = _1] >> 
                -accidentals [phoenix::bind(&results::note::m_accidentals, qi::_val) += _1]
            ;
        }

        qi::rule<Iterator, results::note()> start;
    };

    template<typename Iterator>
    struct extensions_ : qi::grammar<Iterator, results::extensions()>
    {
        extensions_() : 
            extensions_::base_type(start)
        {
            the_extensions = 
                qi::string("b5") [ phoenix::bind(&results::extensions::m_flat5, qi::_val) = true ] | 
                qi::string("6") [ phoenix::bind(&results::extensions::m_6, qi::_val) = true ] | 
                qi::string("7") [ phoenix::bind(&results::extensions::m_7, qi::_val) = true ] | 
                qi::string("maj7") [ phoenix::bind(&results::extensions::m_major7, qi::_val) = true ] | 
                qi::string("b9") [ phoenix::bind(&results::extensions::m_flat9, qi::_val) = true ] | 
                qi::string("9") [ phoenix::bind(&results::extensions::m_9, qi::_val) = true ] | 
                qi::string("#9") [ phoenix::bind(&results::extensions::m_sharp9, qi::_val) = true ] | 
                qi::string("#11") [ phoenix::bind(&results::extensions::m_sharp11, qi::_val) = true ] | 
                qi::string("11") [ phoenix::bind(&results::extensions::m_11, qi::_val) = true ] | 
                qi::string("b13") [ phoenix::bind(&results::extensions::m_flat13, qi::_val) = true ] | 
                qi::string("13") [ phoenix::bind(&results::extensions::m_13, qi::_val) = true ] 
            ;
        
            comma_separated = 
                the_extensions [ _val |= _1 ]
                >> 
                *(
                    -qi::string(",") 
                    >> 
                    the_extensions [ _val |= _1 ]
                )
            ;

            bracketed = 
                qi::string("(") 
                >> 
                comma_separated [ _val |= _1 ]
                >> 
                qi::string(")");

            start = 
                eps [ _val = results::extensions() ] >> 
                (
                    comma_separated [ _val |= _1 ]
                    >> -bracketed [ _val |= _1 ]
                ) | 
                bracketed [ _val |= _1 ]
            ;
        }

        qi::rule<Iterator, results::extensions()> start;
        qi::rule<Iterator, results::extensions()> the_extensions;
        qi::rule<Iterator, results::extensions()> bracketed;
        qi::rule<Iterator, results::extensions()> comma_separated;
    };


    template<typename Iterator>
    struct chord_ : qi::grammar<Iterator, results::chord()>
    {

        note_<Iterator> note;
        extensions_<Iterator> extensions;

        chord_() : 
            chord_::base_type(start)
        {
            start =  
                eps  [ _val = results::chord() ] >> 
                note [ phoenix::bind(&results::chord::m_note, qi::_val) = _1 ] [ phoenix::bind(&results::chord::m_slash_note, qi::_val) = _1 ] >> 
                -(
                    extensions [ phoenix::bind(&results::chord::m_extensions, qi::_val) |= _1 ] 
                    | 
                    (
                        (
                            (
                                qi::string("minor") 
                                | 
                                qi::string("min") 
                                | 
                                qi::string("m")
                            ) [ phoenix::bind(&results::chord::m_type, qi::_val) = results::chord::type::MINOR ] 
                            | 
                            qi::string("sus2") [ phoenix::bind(&results::chord::m_type, qi::_val) = results::chord::type::SUSPENDED2 ] 
                            |
                            (
                                qi::string("sus4") | 
                                qi::string("sus")
                            ) [ phoenix::bind(&results::chord::m_type, qi::_val) = results::chord::type::SUSPENDED4 ] 
                            | 
                            qi::string("dim") [ phoenix::bind(&results::chord::m_type, qi::_val) = results::chord::type::DIMINISHED ] 
                            | 
                            qi::string("aug") [ phoenix::bind(&results::chord::m_type, qi::_val) = results::chord::type::AUGMENTED ] 
                        ) >> 
                        -extensions [ phoenix::bind(&results::chord::m_extensions, qi::_val) |= _1 ]
                    )
                ) >> 
                -(
                    '/' >> 
                    note [ phoenix::bind(&results::chord::m_slash_note, qi::_val) = _1 ]
                )
            ;
        }

        qi::rule<Iterator, results::chord()> start;
    };
}

