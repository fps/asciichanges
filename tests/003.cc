#include <asciichanges/song.h>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> tests = 
    { 
        "",

        " ",

        "   ",

        "  Cm7",
       
        "Eb   ",

        "Eb   \n",

        "\nEb   ",

         "Cm7",
        
        "Eb",
        
        "-- This is a comment",

        "\n-- This is a comment",

        "-- This is a comment\n",
        
        "  \n-- This is a comment\n   ",

        "Tempo: 120",

        "Beat: 7/8",
     
        "Beat: 9/5; Style: Swing",

        "| Am7 |",
        
        "|   |  |  |",

        "-- Autumn Leaves\n"
        "\n"
        "Tempo: 120\n"
        "Time: 4/4 \n"
        "   \n"
        "-- A: \n"
        "|: Cm7     | F7       |    Bbmaj7     | Ebmaj7        | \n"
        "|  Am7b5   | D7b9     | 1. Gm         | G7b9         :|    \n"
        "                      | 2. Gm         |               |\n"
        " \n"
        "-- B: \n"
        "| Am7b5    | D7b9     | Gm            | G7b9          |\n"
        "| Cm7      | F7       | Bbmaj7        | Ebmaj7        |\n"
        "| Am7b5    | D7b9     | Gm / Gm/Gb /  | Gm/F / Gm/E / |\n"
        "| Ebmaj7   | D7b9     | (+) Gm        | (G7b9)        |\n"
        "\n"
        "| (+) Gdim | Gmin(maj7,9) | \n"
    };

    typedef std::string::const_iterator iterator;
    asciichanges::song_<iterator> parser;

    for (const auto &test : tests)
    {
        std::cout << "\"" << test << "\":" << std::endl;

        iterator iter = test.begin();
        iterator end = test.end();

        asciichanges::song result;

        bool r = boost::spirit::qi::phrase_parse(iter, end, parser, boost::spirit::ascii::space, result);

        std::cout << "\t" << r << " " << (iter - test.begin()) << "/" << (end - test.begin()) << " "  << "parsed: " << (r && (end - iter == 0)) << " result: " << result << std::endl;
    }
    return 0;
}

