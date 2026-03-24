//
// Created by igork on 22/03/2026.
//

#include "Token.h"

void Token::createNgrams() {
    nGrams.clear();

    std::string tokenValue = getValue();

    // Strip padding if token longer than 5 characters.
    if (tokenValue.length() > 5) {
        std::erase_if(tokenValue, ::isspace);
    }

    // Generate n-grams.
    for (int n = 1; n <= MAX_N_GRAM_LENGTH; ++n) {
        for (int i = 0; i + n <= tokenValue.length(); ++i) {
            std::string nGram = tokenValue.substr(i, n);
            nGrams.emplace_back(n + 1, nGram);
        }
    }
}
