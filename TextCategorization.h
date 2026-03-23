//
// Created by igork on 22/03/2026.
//

#ifndef RV1_TEXTCATEGORIZATION_H
#define RV1_TEXTCATEGORIZATION_H
#include <regex>
#include <string>
#include <vector>

#include "Token.h"


class TextCategorization {
    std::vector<Token> tokens;

public:
    void tokenize(const std::string& text);

    void generateProfile(const std::string& fileName);

    std::vector<Token> getTokens() {
        return tokens;
    }
};


#endif //RV1_TEXTCATEGORIZATION_H