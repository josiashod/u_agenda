#ifndef __UAGENDA_PARSER_H__
#define __UAGENDA_PARSER_H__

#include <regex>

const std::regex ATTRIBUTE_PARSER{R"("(\w+)\": ?\"(.+)\")"};

struct attr{
    std::string key, value;
};

attr value(const std::string &);

#endif
