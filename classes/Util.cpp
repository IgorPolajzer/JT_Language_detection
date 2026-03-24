//
// Created by igork on 23/03/2026.
//

#include "Util.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

bool Util::cmp(std::pair<std::string, int>& a,
         std::pair<std::string, int>& b)
{
    return a.second > b.second;
}

void Util::writeSortedMapToFile(std::map<std::string, int> M, const std::string& fileName)
{
    std::vector<std::pair<std::string, int> > A;

    for (auto& it : M) {
        A.emplace_back(it);
    }

    // Sort using comparator function
    std::ranges::sort(A.begin(), A.end(), cmp);

    // Print the sorted value
    std::ofstream outFile(fileName);


    if (!outFile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }

    for (auto&[fst, snd] : A) {
        outFile << fst << ';' << snd << '\n';
    }
}