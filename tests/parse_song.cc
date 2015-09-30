#include <asciichanges/parser.h>
#include <iostream>

int main()
{
    asciichanges::song result;

    asciichanges::parse_info info = asciichanges::parse(std::cin, result);

    std::cout << info << std::endl; 

    if (info.successfully_parsed())
    {
        std::cout << result << std::endl;
        return EXIT_SUCCESS;
    }
   
    return EXIT_FAILURE;
}

