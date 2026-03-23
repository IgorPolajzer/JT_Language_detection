#include <iostream>

#include "classes/TextCategorization.h"

void generateProfiles(TextCategorization& textCategorization) {
    const std::vector<std::string> profiles = {"en.txt", "es.txt", "ge.txt", "hr.txt", "si.txt"};

    for (const auto &profile : profiles) {
        textCategorization.generateProfile(profile);
    }
}

void classification(TextCategorization& textCategorization, std::string fileName) {
    std::cout << fileName << std::endl;
}

int main(const int argc, char** argv) {
    TextCategorization textCategorization;

    if (argc < 1) {
        std::cerr << "Usage: " << argv[0] << " <mode: -g or -c>" << std::endl;
        return 1;    
    }

    std::string mode = argv[1];
    if (mode == "-g") {
        generateProfiles(textCategorization);
    } else if (mode == "-c") {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " -c <file-name>" << std::endl;
        }

        classification(textCategorization, argv[2]);
    }

    return 0;
}