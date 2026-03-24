#include <iostream>
#include <vector>
#include <string>
#include "classes/TextCategorization.h"

void generateCorporaProfiles(TextCategorization& textCategorization) {
    const std::vector<std::string> profiles = {"en.txt", "es.txt", "ge.txt", "it.txt", "si.txt"};

    for (const auto &profile : profiles) {
        textCategorization.generateProfile(std::string(TextCategorization::CORPORA_SRC_DIR) + profile, true);
    }
}

void classify(TextCategorization& textCategorization, const std::string& fileName) {
    textCategorization.generateProfile(std::string(TextCategorization::TEST_SRC_DIR) + fileName, false);

    // Strip extension for classification lookup logic.
    std::string baseName = fileName;
    if (size_t lastDot = baseName.find_last_of('.'); lastDot != std::string::npos) {
        baseName.erase(lastDot);
    }

    const Language::Value language = textCategorization.classify(baseName, true);
    std::cout << "The file: '" << fileName << "' was classified as " << Language::toString(language) << std::endl;
}

int main(const int argc, char** argv) {
    TextCategorization textCategorization;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mode: -g or -c>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    if (mode == "-g") {
        generateCorporaProfiles(textCategorization);
    } else if (mode == "-c") {
        if (argc <= 2) {
            std::cerr << "Usage: " << argv[0] << " -c <file-name>" << std::endl;
            return 1;
        }

        classify(textCategorization, argv[2]);
    }

    return 0;
}