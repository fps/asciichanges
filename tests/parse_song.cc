#include <asciichanges/parser.h>
#include <string>
#include <iostream>

#include <boost/spirit/include/support_istream_iterator.hpp>

int main()
{
    asciichanges::song result;

    asciichanges::parse_info info = asciichanges::parse(std::cin, result);

    // std::cout << "\t" << r << " " << (iter - test.begin()) << "/" << (end - test.begin()) << " "  << "parsed: " << (r && (end - iter == 0)) << " result: " << result << std::endl;

    std::cout << info << std::endl; 
    return 0;
}

