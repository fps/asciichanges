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
        bool m_flat5;
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
            m_flat5(false),
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
            m_flat5 |= other.m_flat5;
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
        note m_slash_note;
		
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


        if (the_chord.m_extensions.m_flat5)
            o << " b5";
        if (the_chord.m_extensions.m_6)
            o << " 6";
        if (the_chord.m_extensions.m_major7)
            o << " maj7";
        if (the_chord.m_extensions.m_7)
            o << " 7";
        if (the_chord.m_extensions.m_flat9)
            o << " b9";
        if (the_chord.m_extensions.m_9)
            o << " 9";
        if (the_chord.m_extensions.m_sharp9)
            o << " #9";
        if (the_chord.m_extensions.m_11)
            o << " 11";
        if (the_chord.m_extensions.m_sharp11)
            o << " #11";
        if (the_chord.m_extensions.m_13)
            o << " 13";
        if (the_chord.m_extensions.m_flat13)
            o << " b13";

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
    struct extensions_ : qi::grammar<Iterator, extensions()>
    {
        extensions_() : 
            extensions_::base_type(start)
        {
            using qi::eps;
            using qi::_val;
            using qi::_1;

            the_extensions = 
                qi::string("b5") [ phoenix::bind(&extensions::m_flat5, qi::_val) = true ] | 
                qi::string("6") [ phoenix::bind(&extensions::m_6, qi::_val) = true ] | 
                qi::string("7") [ phoenix::bind(&extensions::m_7, qi::_val) = true ] | 
                qi::string("maj7") [ phoenix::bind(&extensions::m_major7, qi::_val) = true ] | 
                qi::string("b9") [ phoenix::bind(&extensions::m_flat9, qi::_val) = true ] | 
                qi::string("9") [ phoenix::bind(&extensions::m_9, qi::_val) = true ] | 
                qi::string("#9") [ phoenix::bind(&extensions::m_sharp9, qi::_val) = true ] | 
                qi::string("#11") [ phoenix::bind(&extensions::m_sharp11, qi::_val) = true ] | 
                qi::string("11") [ phoenix::bind(&extensions::m_11, qi::_val) = true ] | 
                qi::string("b13") [ phoenix::bind(&extensions::m_flat13, qi::_val) = true ] | 
                qi::string("13") [ phoenix::bind(&extensions::m_13, qi::_val) = true ] 
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
                eps [ _val = extensions() ] >> 
                (
                    comma_separated [ _val |= _1 ]
                    >> -bracketed [ _val |= _1 ]
                ) | 
                bracketed [ _val |= _1 ]
            ;
        }

        qi::rule<Iterator, extensions()> start;
		qi::rule<Iterator, extensions()> the_extensions;
		qi::rule<Iterator, extensions()> bracketed;
		qi::rule<Iterator, extensions()> comma_separated;
    };


    template<typename Iterator>
    struct chord_ : qi::grammar<Iterator, chord()>
    {

        note_<Iterator> note;
        extensions_<Iterator> extensions;

        chord_() : 
            chord_::base_type(start)
        {
			using qi::eps;
			using qi::_val;
			using qi::_1;

            start =  
				eps  [ _val = chord() ] >> 
				note [ phoenix::bind(&chord::m_note, qi::_val) = _1 ] [ phoenix::bind(&chord::m_slash_note, qi::_val) = _1 ] >> 
				-(
                    extensions [ phoenix::bind(&chord::m_extensions, qi::_val) |= _1 ] 
                    | 
                    (
                        (
                            (
                                qi::string("minor") 
                                | 
                                qi::string("min") 
                                | 
                                qi::string("m")
                            ) [ phoenix::bind(&chord::m_type, qi::_val) = chord::type::MINOR ] 
                            | 
                            qi::string("sus2") [ phoenix::bind(&chord::m_type, qi::_val) = chord::type::SUSPENDED2 ] 
                            |
                            (
                                qi::string("sus4") | 
                                qi::string("sus")
                            ) [ phoenix::bind(&chord::m_type, qi::_val) = chord::type::SUSPENDED4 ] 
                            | 
                            qi::string("dim") [ phoenix::bind(&chord::m_type, qi::_val) = chord::type::DIMINISHED ] 
                            | 
                            qi::string("aug") [ phoenix::bind(&chord::m_type, qi::_val) = chord::type::AUGMENTED ] 
                        ) >> 
                        -extensions [ phoenix::bind(&chord::m_extensions, qi::_val) |= _1 ]
                    )
                ) >> 
                -(
                    '/' >> 
                    note [ phoenix::bind(&chord::m_slash_note, qi::_val) = _1 ]
                )
            ;
        }

        qi::rule<Iterator, chord()> start;
    };
}

