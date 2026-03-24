#include <iostream>

#include "classes/TextCategorization.h"

void generateCorporaProfiles(TextCategorization& textCategorization) {
    const std::vector<std::string> profiles = {"en.txt", "es.txt", "ge.txt", "hr.txt", "si.txt"};

    for (const auto &profile : profiles) {
        textCategorization.generateProfile(TextCategorization::LANGUAGE_CORPUS_FOLDER + profile, true);
    }
}

void classify(TextCategorization& textCategorization, const std::string& fileName) {
    textCategorization.generateProfile(TextCategorization::TEST_FILES_FOLDER + fileName);
    textCategorization.classify(TextCategorization::TEST_FILES_FOLDER + "en_test_profile");
}

int main(const int argc, char** argv) {
    TextCategorization textCategorization;

    if (argc < 1) {
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