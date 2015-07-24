#pragma once

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>


#include <ostream>

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

        extensions &operator|=(const extensions &other)
        {
            m_b5 |= other.m_b5;
            m_6 |= other.m_6;
            m_7 |= other.m_7;
            m_major7 |= other.m_major7;
            m_flat9 |= other.m_flat9;
            m_9 |= other.m_9;
            m_sharp9 |= other.m_sharp9;
            m_11 |= other.m_11;
            m_sharp11 |= other.m_sharp11;
            m_flat13 |= other.m_flat13;
            m_13 |= other.m_13;
            return *this;
        }
    };

	struct chord
	{
        note m_note;
		
		enum type { MAJOR, MINOR, AUGMENTED, DIMINISHED, SUSPENDED2, SUSPENDED4 } m_type;

        extensions m_extensions;

        chord() :
            m_type(type::MAJOR)
        {

        }
	};

    std::ostream& operator<<(std::ostream &o, const chord& the_chord)
    {
        switch (the_chord.m_note.m_name)
        {
            case note::name::C:
                o << "C";
                break;
            case note::name::D:
                o << "D";
                break;
            case note::name::E:
                o << "E";
                break;
            case note::name::F:
                o << "F";
                break;
            case note::name::G:
                o << "G";
                break;
            case note::name::A:
                o << "A";
                break;
            case note::name::B:
                o << "B";
                break;
        }

        o << " " << the_chord.m_note.m_accidentals << " ";

        switch (the_chord.m_type)
        {
            case chord::type::MAJOR:
                o << "MAJOR";
                break;
            case chord::type::MINOR:
                o << "MINOR";
                break;
            case chord::type::DIMINISHED:
                o << "DIMINISHED";
                break;
            case chord::type::AUGMENTED:
                o << "AUGMENTED";
                break;
            case chord::type::SUSPENDED2:
                o << "SUSPENDED2";
                break;
            case chord::type::SUSPENDED4:
                o << "SUSPENDED4";
                break;
        }

        return o;
    }

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
            using qi::eps;
            using qi::_val;
            using qi::_1;

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

			start = 
                eps [ _val = extensions() ] >> 
                (
                    comma_separated 
                    >> -bracketed
                ) | 
                bracketed;
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
				eps  [ _val = chord() ] >> 
				note [ phoenix::bind(&chord::m_note, qi::_val) = _1 ] >> 
				-(
                    extensions | 
                    (
                        (
                            minor | 
                            suspended | 
                            qi::string("dim") | 
                            qi::string("aug")
                        ) >> 
                        -extensions
                    )
                ) >> 
                -(
                    '/' >> 
                    note
                )
            ;
        }

        qi::rule<Iterator, chord()> start;
    };
}

