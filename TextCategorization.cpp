//
// Created by igork on 22/03/2026.
//

#include "TextCategorization.h"

#include <fstream>
#include <iostream>

void TextCategorization::generateProfile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string stringFile = buffer.str();
    stringFile = stringFile.substr(0, stringFile.find_last_not_of(" \t\n\r") + 1);

    tokenize(stringFile);
}

void TextCategorization::tokenize(const std::string& text) {
    std::regex wordRegex("[A-Za-z']+");
    const auto wordsBegin = std::sregex_iterator(text.begin(), text.end(), wordRegex);
    const auto wordsEnd = std::sregex_iterator();

    tokens.clear();
    for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
        std::string token = " " + i->str() + " ";

        // Pad token with spaces.
        tokens.emplace_back(token);
    }
}
