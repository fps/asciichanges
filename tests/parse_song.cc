#include <asciichanges/parser.h>
#include <iostream>

int main()
{
    asciichanges::song result;

    asciichanges::parse_info info = asciichanges::parse(std::cin, result);

    std::cout << info << std::endl; 

    if (info.successfully_parsed())
    {
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}

