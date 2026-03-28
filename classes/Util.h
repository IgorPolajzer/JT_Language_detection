//
// Created by igork on 23/03/2026.
//

#ifndef RV1_UTIL_H
#define RV1_UTIL_H
#include <map>
#include <string>
#include <utility>

#include "Language.h"


class Util {
public:
    static bool cmp(std::pair<std::string, int>& a, std::pair<std::string, int>& b);
    static void writeSortedMapToFile(const std::map<std::string, int> &M, const std::string &fileName);
    static bool cmpLanguageDistance(std::pair<Language::Value, size_t>& a,std::pair<Language::Value, size_t>& b);
};


#endif //RV1_UTIL_H