#include <asciichanges/chords.h>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> tests = { "", " ", "x", "c", "C", "D", "E", "F", "G", "B", "A", "Cb", "Cbb", "D#b", "Db#", "D##", "Dbm", "Ebmin", "Abminor", "Bbmin7", "Cm7b5", "Eb7b9b13/G", "CbDb/G#", "Dbmaj7", "G#minmaj7", "Am9/F#", "Ab7#11", "Gsus", "Absus2", "G#sus4(11)", "Am/Gb", "Eb9", "Ebm11", "A#m711", "Bm(71113)", "Am7,9,b13", "Cm(7,#9,13)", "Dm7(b9,b13)", "Am7(b9)", "Eb7(#11)", "A#dim7(#11)", "Faug(11)"};

    typedef std::string::const_iterator iterator;
    asciichanges::chord_<iterator> parser;

    for (const auto &test : tests)
    {
        std::cout << "\"" << test << "\": ";

        iterator iter = test.begin();
        iterator end = test.end();

        asciichanges::chord result;

        bool r = boost::spirit::qi::parse(iter, end, parser, result);

        std::cout << r << " " << (end - iter) << std::endl << "\t " << (r && (end - iter == 0)) << " result: " << result << std::endl;
    }
    return 0;
}

