//
// Created by igork on 22/03/2026.
//

#include "TextCategorization.h"

#include <fstream>
#include <iostream>

#include "Util.h"

std::string TextCategorization::readFileToString(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }

    // Read file into a string representation.
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string stringFile = buffer.str();
    return stringFile.substr(0, stringFile.find_last_not_of(" \t\n\r") + 1);
}

std::vector<std::pair<std::string, size_t>> TextCategorization::readProfileToVector(const std::string& fileName) {
    std::vector<std::pair<std::string, size_t>> profile;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
    }

    std::string line;
    while (getline(file, line)) {
        try {
            static const std::regex profileEntryRegex("[A-Za-z' ]+;[0-9]+");

            if (!std::regex_match(line, profileEntryRegex)) {
                std::cerr << "Line in profile: '" << line << "' couldnt be processed." << std::endl;
                continue;
            }

            const size_t pos = line.find(';');
            const std::string token = line.substr(0, pos);
            const int frequency = std::stoi(line.substr(pos + 1));

            profile.emplace_back(token, frequency);
        } catch (...) {
            std::cerr << "An exception occured while processing '" << line << "' in the language profile" << std::endl;
        }
    }

    file.close();

    return profile;
}

void TextCategorization::generateProfile(const std::string& fileName, bool corporaProfile) {
    // Generate the profile.
    const std::string fileString = readFileToString(fileName);
    tokenize(fileString);
    for (auto& token : tokens) token.createNgrams();
    hashFrequencies();

    // Store the profile.
    std::string outFileName = fileName;
    const std::string suffix = ".txt";

    if (const std::size_t suffixPos = outFileName.rfind(suffix); suffixPos != std::string::npos) {
        outFileName.erase(suffixPos, suffix.size());
    }
    if (const std::size_t folderSlash = outFileName.rfind('/'); folderSlash != std::string::npos) {
        outFileName.erase(0, folderSlash + 1);
    }

    std::string folderSuffix = corporaProfile == true ? LANGUAGE_CORPUS_FOLDER : TEST_FILES_FOLDER;
    Util::writeSortedMapToFile(frequencies, PROFILE_FOLDER + folderSuffix + outFileName + "_profile.txt");
}

void TextCategorization::tokenize(const std::string& text) {
    static const std::regex wordRegex("[A-Za-z']+");
    const auto wordsBegin = std::sregex_iterator(text.begin(), text.end(), wordRegex);
    const auto wordsEnd = std::sregex_iterator();

    tokens.clear();
    for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
        // Pad token with spaces.
        tokens.emplace_back(" " + i->str() + " ");
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

Language TextCategorization::classify(const std::string& fileName) {
    std::vector profile = readProfileToVector(PROFILE_FOLDER + fileName);
    std::vector<std::pair<Language, size_t>> distances;


}
