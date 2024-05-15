#ifndef __UAGENDA_PARSER_H__
#define __UAGENDA_PARSER_H__

#include <regex>

const std::regex ATTRIBUTE_PARSER{R"("(.+)\": ?\"(.+)\")"};
const std::regex KEY_PARSER{R"("(\w+)\":)"};

struct attr{
    std::string key, value;
};

attr attribute_extrator(const std::string &);
// std::string key_extractor(const std::string &);

#endif
