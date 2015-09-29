#include <asciichanges/parser.h>
#include <string>
#include <iostream>

#include <boost/spirit/include/support_istream_iterator.hpp>

int main()
{
    asciichanges::song result;

    asciichanges::parse_info info = asciichanges::parse(std::cin, result);

    std::cout << info << std::endl; 
    return 0;
}

