#pragma once

#include <asciichanges/results.h>
#include <asciichanges/parse_info.h>

#include <iostream>
#include <istream>

namespace asciichanges
{
    parse_info parse(const std::string &s, song &result);

    parse_info parse(std::istream &i, song &result);
}

