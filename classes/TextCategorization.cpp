//
// Created by igork on 22/03/2026.
//

#include "TextCategorization.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "Util.h"

std::string TextCategorization::readFileToString(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return "";
    }

    // Read file into a string representation.
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string stringFile = buffer.str();
    return stringFile.substr(0, stringFile.find_last_not_of(" \t\n\r") + 1);
}

std::map<std::string, std::pair<size_t, size_t>> TextCategorization::readProfileToVector(const std::string& fileName) {
    std::map<std::string, std::pair<size_t, size_t>> profile;
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Failed to open profile: " << fileName << std::endl;
        return profile;
    }

    std::string line;
    size_t index = 0;
    std::string buff;
    while (std::getline(file, buff)) ++index;

    file.clear();
    file.seekg(0, std::ios::beg);

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

            profile[token] = std::pair(index, frequency);
            index--;
        } catch (...) {
            std::cerr << "An exception occured while processing '" << line << "' in the language profile" << std::endl;
        }
    }

    file.close();
    return profile;
}

void TextCategorization::generateProfile(const std::string& filePath, bool corporaProfile) {
    const std::string fileString = readFileToString(filePath);
    tokenize(fileString);
    for (auto& token : tokens) token.createNgrams();
    hashFrequencies();

    // Store the profile.
    std::string baseName= filePath;
    if (const std::size_t lastSlash = baseName.find_last_of("/\\"); lastSlash != std::string::npos) {
        baseName.erase(0, lastSlash + 1);
    }
    if (const std::size_t lastDot = baseName.find_last_of('.'); lastDot != std::string::npos) {
        baseName.erase(lastDot);
    }

    std::string targetDir = corporaProfile ? CORPORA_PROFILE_DIR : TEST_PROFILE_DIR;
    Util::writeSortedMapToFile(frequencies, targetDir + baseName + "_profile.txt");
}

void TextCategorization::tokenize(const std::string& text) {
    static const std::regex wordRegex("[A-Za-z']+");
    const auto wordsBegin = std::sregex_iterator(text.begin(), text.end(), wordRegex);
    const auto wordsEnd = std::sregex_iterator();

    tokens.clear();
    for (std::sregex_iterator i = wordsBegin; i != wordsEnd; ++i) {
        tokens.emplace_back(" " + i->str() + " ");
    }
}

void TextCategorization::hashFrequencies() {
    frequencies.clear();
    for (auto& token : tokens) {
        for (const auto& nGram : token.getNgrams()) {
            frequencies[nGram.second]++;
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

Language::Value TextCategorization::classify(const std::string &profileName) {
    std::map<std::string, std::pair<size_t, size_t>> documentProfile = readProfileToVector(TEST_PROFILE_DIR + profileName + "_profile.txt");
    std::vector<std::pair<Language::Value, size_t>> distances;

    try {
        if (std::filesystem::exists(CORPORA_PROFILE_DIR) && std::filesystem::is_directory(CORPORA_PROFILE_DIR)) {
            // Compare to all corpora profiles on the system.
            for (const auto& corporaProfile : std::filesystem::directory_iterator(CORPORA_PROFILE_DIR)) {
                if (corporaProfile.is_regular_file()) {
                    size_t totalDistance = 0;
                    std::map<std::string, std::pair<size_t, size_t>> categoryProfile = readProfileToVector(corporaProfile.path().string());
                    const size_t outOfPlace = categoryProfile.size();

                    // Measure distances between category and document profile.
                    for (const auto& profileEntry : documentProfile) {
                        std::string nGram = profileEntry.first;
                        size_t distance = categoryProfile.contains(nGram)
                            ? std::abs(static_cast<long long>(documentProfile.at(nGram).second) - static_cast<long long>(categoryProfile[nGram].second)) : outOfPlace;
                        totalDistance += distance;
                    }

                    distances.emplace_back(Language::fromProfile(corporaProfile.path().filename().string()), totalDistance);
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing profiles: " << e.what() << std::endl;
    }

    int minDistance = INT_MAX;
    Language::Value minDistanceLanguage = Language::UNKNOWN;
    for (const auto& distance : distances) {
        if (distance.second < minDistance) {
            minDistance = distance.second;
            minDistanceLanguage = distance.first;
        }
    }

    return minDistanceLanguage;
}