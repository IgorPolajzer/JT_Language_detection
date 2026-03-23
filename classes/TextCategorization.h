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
    static constexpr std::string LANGUAGE_CORPUS_FOLDER = "languages/";
    static constexpr std::string PROFILE_FOLDER = "profiles/";

    std::vector<Token> tokens;
    std::map<std::string, int> frequencies;
public:
    void generateProfile(const std::string& fileName);
    void tokenize(const std::string& text);
    void hashFrequencies();
    void printNGrams() const;
    void printFrequencies() const;

    std::vector<Token> getTokens() {
        return tokens;
    }
};


#endif //RV1_TEXTCATEGORIZATION_H