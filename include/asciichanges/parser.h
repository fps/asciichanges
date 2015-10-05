#pragma once

#include <asciichanges/results.h>
#include <asciichanges/parse_info.h>

#include <iostream>
#include <istream>

namespace asciichanges
{
    parse_info parse(const std::string &s, results::song &result);

    parse_info parse(std::istream &i, results::song &result);
}

