//
// Created by igork on 23/03/2026.
//

#ifndef RV1_UTIL_H
#define RV1_UTIL_H
#include <map>
#include <string>
#include <utility>


class Util {
public:
    static bool cmp(std::pair<std::string, int>& a, std::pair<std::string, int>& b);
    static void writeSortedMapToFile(std::map<std::string, int> M, std::string fileName);
};


#endif //RV1_UTIL_H