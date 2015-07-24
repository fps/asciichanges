#pragma once

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

namespace asciichanges
{
    namespace qi = boost::spirit::qi;
	namespace phoenix = boost::phoenix;

    struct note
    {
        enum name { C, D, E, F, G, A, B} m_name;
        int m_accidentals;

        note() :
            m_name(name::C),
            m_accidentals(0)
        {

        }
    };

    struct extensions
    {
        bool m_b5;
        bool m_6;
        bool m_7;
        bool m_major7;
        bool m_flat9;
        bool m_9;
        bool m_sharp9;
        bool m_11;
        bool m_sharp11;
        bool m_flat13;
        bool m_13;

        extensions() :
            m_b5(false),
            m_6(false),
            m_7(false),
            m_major7(false),
            m_flat9(false),
            m_9(false),
            m_sharp9(false),
            m_11(false),
            m_sharp11(false),
            m_flat13(false),
            m_13(false)
        {

        }
    };

	struct chord
	{
        note m_note;
		
		enum type { MAJOR, MINOR, AUGMENTED, DIMINISHED, SUSPENDED2, SUSPENDED4 } m_type;

        extensions m_extensions;
	};


    struct abcdefg_ : qi::symbols<char, note::name>
    {
        abcdefg_()
        {
            add
                ("C", note::name::C)
                ("D", note::name::D)
                ("E", note::name::E)
                ("F", note::name::F)
                ("G", note::name::G)
                ("A", note::name::A)
                ("B", note::name::B)
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
			using qi::_val;
			using qi::_1;

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
    struct note_ : qi::grammar<Iterator, note()>
    {
        accidentals_<Iterator> accidentals;

        note_() : 
            note_::base_type(start)
        {
			using qi::eps;
			using qi::_val;
			using qi::_1;

            start = 
				eps [_val = note()] >>
				abcdefg      [phoenix::bind(&note::m_name, qi::_val) = _1] >> 
				-accidentals [phoenix::bind(&note::m_accidentals, qi::_val) += _1]
            ;
        }

        qi::rule<Iterator, note()> start;
    };

    template<typename Iterator>
    struct minor_ : qi::grammar<Iterator, chord::type()>
    {
        minor_() : 
            minor_::base_type(start)
        {
            using qi::eps;
            using qi::_val;

            start = 
                (
                    qi::string("minor") | 
                    qi::string("min") | 
                    qi::string("m")
                ) [_val = chord::type::MINOR ]
            ;
        }

        qi::rule<Iterator, chord::type()> start;
    };

    template<typename Iterator>
    struct suspended_ : qi::grammar<Iterator, chord::type()>
    {
        suspended_() : 
            suspended_::base_type(start)
        {
            using qi::eps;
            using qi::_val;

            start = 
                qi::string("sus4") [ _val = chord::type::SUSPENDED4 ] | 
                qi::string("sus2") [ _val = chord::type::SUSPENDED2 ] | 
                qi::string("sus")  [ _val = chord::type::SUSPENDED2 ]
            ;
        }

        qi::rule<Iterator, chord::type()> start;
    };

    template<typename Iterator>
    struct extensions_ : qi::grammar<Iterator, extensions()>
    {
        extensions_() : 
            extensions_::base_type(start)
        {
            the_extensions = 
                qi::string("b5") | 
                qi::string("6") | 
                qi::string("7") | 
                qi::string("maj7") | 
                qi::string("b9") | 
                qi::string("9") | 
                qi::string("#9") | 
                qi::string("#11") | 
                qi::string("11") | 
                qi::string("b13") | 
                qi::string("13")
            ;
		
			comma_separated = the_extensions >> *(-qi::string(",") >> the_extensions);

			bracketed = qi::string("(") >> comma_separated >> qi::string(")");

			start = (comma_separated >> -bracketed) | bracketed;
        }

        qi::rule<Iterator, extensions()> start;
		qi::rule<Iterator> the_extensions;
		qi::rule<Iterator> bracketed;
		qi::rule<Iterator> comma_separated;
    };


    template<typename Iterator>
    struct chord_ : qi::grammar<Iterator, chord()>
    {

        note_<Iterator> note;
        minor_<Iterator> minor;
        suspended_<Iterator> suspended;
        extensions_<Iterator> extensions;

        chord_() : 
            chord_::base_type(start)
        {
			using qi::eps;
			using qi::_val;
			using qi::_1;

            start =  
				eps[_val = chord()] >> 
				note >> 
				-(extensions | ((minor | suspended | qi::string("dim") | qi::string("aug")) >> -extensions)) >> -('/' >> note);
        }

        qi::rule<Iterator, chord()> start;
    };
}

