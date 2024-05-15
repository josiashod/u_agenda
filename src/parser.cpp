#include "parser.h"

attr attribute_extrator(const std::string &str)
{
    std::smatch matches;
    auto it = std::sregex_iterator(str.begin(), str.end(), ATTRIBUTE_PARSER);
    auto end = std::sregex_iterator();
    matches = *it;

    if(matches.size() > 1)
        return {matches[1].str(), matches[2].str()};
    else
        return {"", ""};
}

// std::string key_extractor(const std::string &str)
// {
//     std::smatch matches;
//     auto it = std::sregex_iterator(str.begin(), str.end(), KEY_PARSER);
//     auto end = std::sregex_iterator();

//     matches = *it;
//     if(matches.size() > 1)
//         return matches[1].str();
//     return "";
// }