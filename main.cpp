#include <iostream>

#include "TextCategorization.h"

int main() {
    TextCategorization textCategorization;

    textCategorization.generateProfile("languages/en.txt");

    for (Token token : textCategorization.getTokens()) {
        std::cout << "Token: " << token.getValue() << std::endl;

        token.createNgrams();
        for (int i = 0; i < token.getNgrams().size(); i++) {
            std::cout << token.getNgrams()[i].first << "-gram: " << "|" << token.getNgrams()[i].second << "|" << std::endl;
        }
    }

    return 0;
}
