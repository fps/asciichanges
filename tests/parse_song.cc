#include <asciichanges/parser.h>
#include <string>
#include <iostream>

int main()
{
    asciichanges::song result;

    asciichanges::parse_info info = asciichanges::parse(std::cin, result);

    std::cout << info << std::endl; 
    return 0;
}

