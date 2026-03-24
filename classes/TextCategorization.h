#ifndef RV1_TEXTCATEGORIZATION_H
#define RV1_TEXTCATEGORIZATION_H
#include <regex>
#include <string>
#include <vector>
#include <map>

#include "Language.h"
#include "Token.h"

class TextCategorization {
    std::vector<Token> tokens;
    std::map<std::string, int> frequencies;

    static std::string readFileToString(const std::string& fileName);
    static std::map<std::string, std::pair<size_t, size_t>> readProfileToVector(const std::string& fileName);
    void tokenize(const std::string& text);
    void hashFrequencies();
public:
    // Root input folders.
    static constexpr const char* CORPORA_SRC_DIR = "data/corpora/";
    static constexpr const char* TEST_SRC_DIR = "data/test_files/";

    // Output profile folders.
    static constexpr const char* CORPORA_PROFILE_DIR = "profiles/corpora/";
    static constexpr const char* TEST_PROFILE_DIR = "profiles/test_files/";

    void generateProfile(const std::string& fileName, bool corporaProfile=false);
    void printNGrams() const;
    void printFrequencies() const;

    static Language::Value classify(const std::string &fileName, bool printScore=false);

    std::vector<Token> getTokens() {
        return tokens;
    }
};

#endif //RV1_TEXTCATEGORIZATION_H