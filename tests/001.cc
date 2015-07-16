#include <asciichanges/chords.h>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> tests = { "", " ", "x", "c", "C", "D", "E", "F", "G", "B", "A", "Cb", "Cbb", "D#b", "Db#", "D##" };

    typedef std::string::const_iterator iterator;
    asciichanges::note_<iterator> note;

    for (const auto &test : tests)
    {
        std::cout << "\"" << test << "\": ";

        iterator iter = test.begin();
        iterator end = test.end();

        unsigned result = 0;

        bool r = boost::spirit::qi::phrase_parse(iter, end, note, boost::spirit::ascii::space);

        std::cout << r << " " << (end - iter) << " " << (r && (end - iter == 0)) << std::endl;
    }
    return 0;
}

