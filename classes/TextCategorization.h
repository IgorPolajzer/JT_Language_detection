//
// Created by igork on 22/03/2026.
//

#ifndef RV1_TEXTCATEGORIZATION_H
#define RV1_TEXTCATEGORIZATION_H
#include <regex>
#include <string>
#include <vector>

#include "Language.h"
#include "Token.h"


class TextCategorization {
    std::vector<Token> tokens;
    std::map<std::string, int> frequencies;

    static std::string readFileToString(const std::string& fileName);
    static std::vector<std::pair<std::string, size_t>> readProfileToVector(const std::string& fileName);
    void tokenize(const std::string& text);
    void hashFrequencies();
public:
    static constexpr std::string LANGUAGE_CORPUS_FOLDER = "corpora/";
    static constexpr std::string TEST_FILES_FOLDER = "test_files/";
    static constexpr std::string PROFILE_FOLDER = "profiles/";

    void generateProfile(const std::string& fileName, bool corporaProfile=false);
    void printNGrams() const;
    void printFrequencies() const;
    Language classify(const std::string& fileName);

    std::vector<Token> getTokens() {
        return tokens;
    }
};


#endif //RV1_TEXTCATEGORIZATION_H