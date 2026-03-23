//
// Created by igork on 22/03/2026.
//

#include "TextCategorization.h"

#include <fstream>
#include <iostream>

#include "Util.h"

void TextCategorization::generateProfile(const std::string& fileName) {
    std::ifstream file(LANGUAGE_CORPUS_FOLDER + fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }

    // Read file into a string representation.
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string stringFile = buffer.str();
    stringFile = stringFile.substr(0, stringFile.find_last_not_of(" \t\n\r") + 1);

    // Generate the profile.
    tokenize(stringFile);
    for (auto& token : tokens) token.createNgrams();
    hashFrequencies();

    // Store the profile.
    std::string outFileName = fileName;
    std::string suffix = ".txt";
    const std::size_t suffixPos = outFileName.rfind(suffix);
    if (suffixPos != std::string::npos) outFileName.erase(suffixPos, suffix.size());
    Util::writeSortedMapToFile(frequencies, PROFILE_FOLDER + fileName + "_profile.txt");
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

void TextCategorization::hashFrequencies() {
    for (auto token : tokens) {
        for (const auto& nGram : token.getNgrams()) {
            if (!frequencies.contains(nGram.second)) frequencies[nGram.second] = 1;
            else frequencies[nGram.second]++;
        }
    }
}

void TextCategorization::printNGrams() const {
    for (Token token : tokens) {
        std::cout << "Token: " << token.getValue() << std::endl;
        for (int i = 0; i < token.getNgrams().size(); i++) {
            std::cout << token.getNgrams()[i].first << "-gram: " << "|" << token.getNgrams()[i].second << "|" << std::endl;
        }
    }
}

void TextCategorization::printFrequencies() const {
    for (const auto& [token, count] : frequencies) {
        std::cout << "|" << token << "| : " << count << std::endl;
    }
}
