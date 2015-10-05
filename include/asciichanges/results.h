#pragma once

#include <ostream>

namespace asciichanges
{
    struct note
    {
        enum class name { C, D, E, F, G, A, B};

        name m_name;
        int m_accidentals;

        note() :
            m_name(name::C),
            m_accidentals(0)
        {

        }
    };

    inline std::ostream &operator<<(std::ostream &o, const note& the_note)
    {
        switch (the_note.m_name)
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

        o << " " << the_note.m_accidentals << " ";

        return o;
    }

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

    inline std::ostream& operator<<(std::ostream &o, const chord& the_chord)
    {
        o << the_chord.m_note << " ";

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

        o << " / " << the_chord.m_slash_note;
        return o;
    }

    struct line
    {
        virtual ~line()
        {

        }
    };

    struct keyvalue : line
    {
        std::string key;
        std::string value;

        keyvalue(const std::string k = "", const std::string v = "") :
            key(k),
            value(v)
        {

        }
    };

    inline std::ostream &operator<<(std::ostream &o, const keyvalue &k)
    {
        o << "key: " << k.key << " value: " << k.value;
        return o;
    }

    struct bar_entry
    {
        virtual ~bar_entry()
        {

        }
        
        
    };

    struct bar
    {
        
    };

    struct bars : line
    {

    };

    struct song
    {

    };

    inline std::ostream &operator<<(std::ostream &o, const song &s)
    {
        o << "song";
        return o;
    }
}


