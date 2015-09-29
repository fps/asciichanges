#include <asciichanges/parser.h>
#include <iostream>

int main()
{
    asciichanges::song result;

    asciichanges::parse_info info = asciichanges::parse(std::cin, result);

    std::cout << info << std::endl; 

    return 
        info.successfully_parsed() 
        ? 
            EXIT_SUCCESS 
        : 
            EXIT_FAILURE
    ;
}

